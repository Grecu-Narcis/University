import { Task } from "@/domain/Task";
import { SQLiteDatabase } from "expo-sqlite";

export async function addTaskDb(dbConnection: SQLiteDatabase, task: Task) {
    return dbConnection
    ?.runAsync(
      "INSERT INTO tasks(title, description, dueDate, isCompleted, priority) values (?, ?, ?, ?, ?)",
      task.title,
      task.description,
      task.dueDate.toString(),
      task.isCompleted ? 1 : 0,
      task.priority
    )
}

export async function updateTaskDb(dbConnection: SQLiteDatabase, taskToUpdate: Task) {
    return dbConnection
      ?.runAsync(
        "UPDATE tasks\
      SET title=?, description=?, dueDate=?, isCompleted=?, priority=? where id=?",
        taskToUpdate.title,
        taskToUpdate.description,
        taskToUpdate.dueDate.toString(),
        taskToUpdate.isCompleted ? 1 : 0,
        taskToUpdate.priority,
        taskToUpdate.taskId
      )
}

export async function deleteTaskDb(dbConnection: SQLiteDatabase, taskId: number) {
    return dbConnection
      ?.runAsync("DELETE FROM tasks where id = ?", taskId)
}