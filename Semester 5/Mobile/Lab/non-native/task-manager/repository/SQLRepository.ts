import { Task } from "@/domain/Task";
import { SQLiteDatabase } from "expo-sqlite";
import { deleteTaskFromServer, updateTaskOnServer } from "./NetworkRepository";

export async function addTaskDb(dbConnection: SQLiteDatabase, task: Task, taskId?: number) {
  if (taskId == undefined)   
    return dbConnection
      ?.runAsync(
        "INSERT INTO tasks(title, description, dueDate, isCompleted, priority) values (?, ?, ?, ?, ?)",
        task.title,
        task.description,
        task.dueDate.toString(),
        task.isCompleted ? 1 : 0,
        task.priority
      )

      return dbConnection
      ?.runAsync(
        "INSERT OR REPLACE INTO tasks(id, title, description, dueDate, isCompleted, priority) values (?, ?, ?, ?, ?, ?)",
        taskId,
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


export const addToSyncQueue = async (
  connection: SQLiteDatabase,
  taskId: number,
  syncAction: string,
  payload: string
) => {
  await connection.runAsync(
    `INSERT INTO sync_queue (taskId, syncAction, payload)
     VALUES (?, ?, ?);`,
    [taskId, syncAction, payload]
  );
};

export const getSyncQueue = async (
  connection: SQLiteDatabase
): Promise<{ id: number; taskId: number; syncAction: string; payload: string }[]> => {
  const result = await connection.getAllAsync(`SELECT * FROM sync_queue`);
  return result.map((row: any) => ({
    id: row.id,
    taskId: row.taskId,
    syncAction: row.syncAction,
    payload: row.payload,
  }));
};

export const removeFromSyncQueue = async (
  connection: SQLiteDatabase,
  id: number
) => {
  await connection.runAsync(`DELETE FROM sync_queue WHERE id = ?;`, [id]);
};

export const syncPendingOperations = async (dbConnection: SQLiteDatabase) => {
  try {
    const pendingOperations = await getSyncQueue(dbConnection);

    for (const operation of pendingOperations) {
      const { id, taskId, syncAction, payload } = operation;

      try {
        if (syncAction === "UPDATE" && payload) {
          const task = JSON.parse(payload);
          const newTask = {
            ...task,
            dueDate: new Date(task.dueDate)
          }
          
          await updateTaskOnServer(newTask);
        } else if (syncAction === "DELETE") {
          await deleteTaskFromServer(taskId);
        }

        // Remove successfully synced operation from the queue
        await removeFromSyncQueue(dbConnection!, id);
      } catch (syncError) {
        console.error(`Failed to sync operation with id ${id}:`, syncError);
      }
    }
  } catch (error) {
    console.error("Error fetching pending operations from sync_queue:", error);
  }
};