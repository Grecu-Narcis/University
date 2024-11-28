import { TaskPriority } from "./TaskPriority";

export interface Task {
    taskId: string;
    title: string;
    description: string;
    dueDate: Date;
    isCompleted: boolean;
    priority: TaskPriority;
}