import { TaskPriority } from "./TaskPriority";

export interface Task {
    taskId: number;
    title: string;
    description: string;
    dueDate: Date;
    isCompleted: boolean;
    priority: TaskPriority;
}