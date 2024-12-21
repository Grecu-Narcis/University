import { demoTasks } from "@/constants/tasks";
import { Task } from "@/domain/Task";
import { createContext, ReactNode, useEffect, useState } from "react";
import * as SQLite from "expo-sqlite";
import { getPriorityFromString } from "@/domain/TaskPriority";
import {
  addTaskDb,
  deleteTaskDb,
  updateTaskDb,
} from "@/repository/SQLRepository";
import { showMessage } from "react-native-flash-message";

export type TaskContextProps = {
  tasks: Task[];
  addTask: (task: Task) => void;
  updateTask: (task: Task) => void;
  deleteTask: (taskId: number) => void;
  getTask: (taskId: number) => Task | undefined;
};

export type TaskContextProviderType = {
  children: ReactNode;
};

export const TaskContext = createContext<TaskContextProps | null>(null);

export default function TaskContextProvider({
  children,
}: TaskContextProviderType) {
  const [tasks, setTasks] = useState<Task[]>([]);
  const [dbConnection, setDbConnection] = useState<SQLite.SQLiteDatabase>();

  const addTask = (task: Task) => {
    addTaskDb(dbConnection!, task)
      .then((result) => {
        const insertedId = result.lastInsertRowId;
        const newTask = { ...task, taskId: insertedId };

        setTasks([...tasks, newTask]);
      })
      .catch((error) => {
        throw new Error("Failed to save task!");
      });
  };

  const updateTask = (taskToUpdate: Task) => {
    // throw new Error("Test");
    updateTaskDb(dbConnection!, taskToUpdate)
      .then((result) =>
        setTasks(
          tasks.map((task) =>
            task.taskId === taskToUpdate.taskId ? taskToUpdate : task
          )
        )
      )
      .catch((error) => {
        throw new Error("Failed to update task!");
      });
  };

  const deleteTask = (taskId: number) => {
    deleteTaskDb(dbConnection!, taskId)
      .then((result) =>
        setTasks(tasks.filter((task) => task.taskId !== taskId))
      )
      .catch((error) => {
        throw new Error("Failed to delete task!");
      });
  };

  const getTask = (taskId: number) => {
    const task = tasks.find((task) => taskId == task.taskId);

    return task;
  };

  useEffect(() => {
    const connection = SQLite.openDatabaseSync("tasks.db");
    setDbConnection(connection);
    createTable(connection);

    try {
      fetchTasks(connection);
    } catch (error) {
      console.error(error);

      showMessage({
        message: "Failed to load tasks",
        type: "warning",
        duration: 2000,
      });
    }
  }, []);

  const createTable = (connection: SQLite.SQLiteDatabase) =>
    connection.execSync(
      "CREATE TABLE IF NOT EXISTS tasks(\
      id INTEGER PRIMARY KEY AUTOINCREMENT,\
      title TEXT not null,\
      description TEXT not null,\
      dueDate TEXT not null,\
      isCompleted INTEGER not null,\
      priority TEXT not null);"
    );

  const fetchTasks = async (connection: SQLite.SQLiteDatabase) => {
    const allTasks = await connection.getAllAsync("SELECT * FROM tasks");
    const tasks: Task[] = [];

    for (const task of allTasks) {
      const taskId = (task as any).id;
      const title = (task as any).title;
      const description = (task as any).description;
      const dueDate = new Date((task as any).dueDate);
      const isCompleted = (task as any).isCompleted == 1 ? true : false;
      const priority = getPriorityFromString((task as any).priority);

      const currentTask: Task = {
        taskId: taskId,
        title: title,
        description: description,
        dueDate: dueDate,
        isCompleted: isCompleted,
        priority: priority,
      };

      tasks.push(currentTask);
    }

    setTasks(tasks);
  };

  return (
    <TaskContext.Provider
      value={{
        tasks: tasks,
        addTask: addTask,
        updateTask: updateTask,
        deleteTask: deleteTask,
        getTask: getTask,
      }}
    >
      {children}
    </TaskContext.Provider>
  );
}
