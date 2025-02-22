import { Task } from "@/domain/Task";

const BASE_API_URL = 'http://172.20.10.2:3000';

export async function getAllFromServer() {
    try {
      const controller = new AbortController();
      const timeout = 1000;
      const timeoutId = setTimeout(() => controller.abort(), timeout);

      console.log("fetch from server begin")
    const response = await fetch(BASE_API_URL + '/tasks', {signal: controller.signal});
    const tasks = await response.json();

      clearTimeout(timeoutId);

    return tasks.map((task: any) => ({
        taskId: task.id,
        title: task.title,
        description: task.description,
        dueDate: new Date(task.dueDate),
        isCompleted: task.isCompleted,
        priority: task.priority,
      }));

    }
    catch (error: any) {
      console.log(error)
      throw new Error();
    }
}

export async function addTaskToServer(task: Task) {
    try {
      const response = await fetch(BASE_API_URL + '/tasks', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          title: task.title,
          description: task.description,
          dueDate: task.dueDate.toISOString(),
          isCompleted: task.isCompleted,
          priority: task.priority,
        }),
      });
      const result: any = await response.json();
      console.log('Task added with ID:', result.id);

      return {
        taskId: result.id,
        title: result.title,
        description: result.description,
        dueDate: new Date(result.dueDate),
        isCompleted: result.isCompleted,
        priority: result.priority,
      };
    } catch (error) {
      console.error('Failed to add task:', error);
    }
  };

export async function updateTaskOnServer(task: Task) {
    try {
      await fetch(`${BASE_API_URL}/tasks/${task.taskId}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          title: task.title,
          description: task.description,
          dueDate: task.dueDate.toISOString(),
          isCompleted: task.isCompleted,
          priority: task.priority,
        }),
      });
    } catch (error) {
      console.error('Failed to update task:', error);
      throw new Error();
    }
};

export async function deleteTaskFromServer(taskId: number) {
    try {
      const controller = new AbortController();
      const timeout = 2000;
      const timeoutId = setTimeout(() => controller.abort(), timeout);

      const response = await fetch(`${BASE_API_URL}/tasks/${taskId}`, { method: 'DELETE', signal: controller.signal });

      if (!response.ok)
        throw new Error();

      console.log(`Task ${taskId} deleted`);
    } catch (error) {
      console.error('Failed to delete task:', error);
      throw new Error();
    }
  };