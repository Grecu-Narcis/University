import { demoTasks } from "@/constants/tasks";
import { Task } from "@/domain/Task";
import { createContext, ReactNode, useState } from "react";

export type TaskContextProps = {
  tasks: Task[];
  addTask: (task: Task) => void;
  updateTask: (task: Task) => void;
  deleteTask: (taskId: string) => void;
  getTask: (taskId: string) => Task | undefined;
};

export type TaskContextProviderType = {
  children: ReactNode;
};

export const TaskContext = createContext<TaskContextProps | null>(null);

export default function TaskContextProvider({
  children,
}: TaskContextProviderType) {
  const [tasks, setTasks] = useState<Task[]>(demoTasks);

  const addTask = (task: Task) => setTasks([...tasks, task]);

  const updateTask = (taskToUpdate: Task) =>
    setTasks(
      tasks.map((task) =>
        task.taskId === taskToUpdate.taskId ? taskToUpdate : task
      )
    );

  const deleteTask = (taskId: string) =>
    setTasks(tasks.filter((task) => task.taskId !== taskId));

  const getTask = (taskId: string) =>
    tasks.find((task) => taskId === task.taskId);

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
