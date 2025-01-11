import { demoTasks } from "@/constants/tasks";
import { Task } from "@/domain/Task";
import { createContext, ReactNode, useEffect, useState } from "react";
import * as SQLite from "expo-sqlite";
import { getPriorityFromString } from "@/domain/TaskPriority";
import {
  addTaskDb,
  addToSyncQueue,
  deleteTaskDb,
  syncPendingOperations,
  updateTaskDb,
} from "@/repository/SQLRepository";
import { showMessage } from "react-native-flash-message";
import {
  addTaskToServer,
  deleteTaskFromServer,
  getAllFromServer,
  updateTaskOnServer,
} from "@/repository/NetworkRepository";

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

  const addTask = async (task: Task) => {
    try {
      const insertedTask = await addTaskToServer(task);
      await addTaskDb(dbConnection!, insertedTask!, insertedTask?.taskId);
      setTasks([...tasks, insertedTask!]);
    } catch (error) {
      throw new Error("Failed to add task!");
    }
  };

  const updateTask = async (taskToUpdate: Task) => {
    try {
      await updateTaskDb(dbConnection!, taskToUpdate);

      setTasks((prevTasks) =>
        prevTasks.map((task) =>
          task.taskId === taskToUpdate.taskId ? taskToUpdate : task
        )
      );

      try {
        await updateTaskOnServer(taskToUpdate);
      } catch (serverError) {
        console.log("Failed to update on server:", serverError);

        await addToSyncQueue(
          dbConnection!,
          taskToUpdate.taskId,
          "UPDATE",
          JSON.stringify(taskToUpdate)
        );
      }
    } catch (dbError) {
      console.error("Failed to update task locally:", dbError);
      throw new Error("Task update failed.");
    }
  };

  const deleteTask = async (taskId: number) => {
    try {
      await deleteTaskDb(dbConnection!, taskId);

      setTasks((prevTasks) =>
        prevTasks.filter((task) => task.taskId !== taskId)
      );

      try {
        await deleteTaskFromServer(taskId);
      } catch (serverError) {
        console.error("Failed to delete on server:", serverError);

        // Add to Sync Queue
        await addToSyncQueue(dbConnection!, taskId, "DELETE", "");
      }
    } catch (dbError) {
      console.error("Failed to delete task locally:", dbError);
      throw new Error("Task deletion failed.");
    }
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
      console.log("start fetch tasks");
      try {
        fetchTasksFromServer();
      } catch (error) {
        console.log("fetch from server failed...");
        console.log("fetching from local db");
        fetchTasks(connection);
      }
    } catch (error) {
      console.error(error);

      showMessage({
        message: "Failed to load tasks",
        type: "warning",
        duration: 2000,
      });
    }

    const syncInterval = setInterval(() => {
      syncPendingOperations(connection);
    }, 1000); // Sync every 60 seconds

    return () => clearInterval(syncInterval);
  }, []);

  // websocket
  useEffect(() => {
    const socket = new WebSocket("ws://192.168.1.136:3001");
    socket.onopen = () => {
      console.log("WebSocket connection established");
    };

    socket.onmessage = async (event) => {
      const { type, payload } = JSON.parse(event.data);

      if (type === "add") {
        const taskToAdd = {
          taskId: payload.id,
          title: payload.title,
          description: payload.description,
          dueDate: new Date(payload.dueDate),
          isCompleted: !!payload.isCompleted,
          priority: payload.priority,
        };

        await addTaskDb(dbConnection!, taskToAdd, taskToAdd.taskId);

        setTasks((prevTasks) => [...prevTasks, taskToAdd]);
      } else if (type === "update") {
        const updatedTask = {
          taskId: payload.id,
          title: payload.title,
          description: payload.description,
          dueDate: new Date(payload.dueDate),
          isCompleted: !!payload.isCompleted,
          priority: payload.priority,
        };

        await updateTaskDb(dbConnection!, payload);
        setTasks((prevTasks) =>
          prevTasks.map((task) =>
            task.taskId == updatedTask.taskId ? updatedTask : task
          )
        );
      } else if (type === "delete") {
        setTasks((prevTasks) =>
          prevTasks.filter((task) => task.taskId != payload.taskId)
        );
      }
    };

    socket.onerror = (error) => {
      console.error("WebSocket error:", error);
    };

    socket.onclose = () => {
      console.log("WebSocket connection closed");
    };

    return () => {
      socket.close();
    };
  }, []);

  const createTable = (connection: SQLite.SQLiteDatabase) => {
    connection.execSync(
      "CREATE TABLE IF NOT EXISTS tasks(\
      id INTEGER PRIMARY KEY AUTOINCREMENT,\
      title TEXT not null,\
      description TEXT not null,\
      dueDate TEXT not null,\
      isCompleted INTEGER not null,\
      priority TEXT not null);"
    );

    connection.execSync(
      `CREATE TABLE IF NOT EXISTS sync_queue (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        taskId INTEGER NOT NULL,
        syncAction TEXT NOT NULL,
        payload TEXT NOT NULL
      );`
    );
  };

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

  const fetchTasksFromServer = async () => {
    let tasks = await getAllFromServer();
    setTasks(tasks);

    tasks.forEach((task: Task) => {
      addTaskDb(dbConnection!, task, task.taskId);
    });

    console.log("fetched tasks from server!");
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
