import { Task } from "@/domain/Task";
import { TaskPriority } from "@/domain/TaskPriority";

let demoTasks: Task[] = [
    {
      taskId: "1",
      title: "Buy groceries",
      description: "Milk, Bread, Eggs, and Vegetables",
      dueDate: new Date("2025-11-01"),
      isCompleted: false,
      priority: TaskPriority.HIGH,
    },
    {
      taskId: "2",
      title: "Finish project report",
      description: "Complete the annual project report and submit it to the manager",
      dueDate: new Date("2024-11-05"),
      isCompleted: false,
      priority: TaskPriority.MEDIUM,
    },
    {
      taskId: "3",
      title: "Workout",
      description: "Complete 30-minute cardio session",
      dueDate: new Date("2025-10-30"),
      isCompleted: true,
      priority: TaskPriority.LOW,
    },
    {
      taskId: "4",
      title: "Book doctor’s appointment",
      description: "Check knee injury",
      dueDate: new Date("2024-11-10"),
      isCompleted: false,
      priority: TaskPriority.MEDIUM,
    },
    {
      taskId: "5",
      title: "Read a book",
      description: "Start reading 'Atomic Habits'",
      dueDate: new Date("2024-12-24"),
      isCompleted: false,
      priority: TaskPriority.LOW,
    },

    {
      taskId: "6",
      title: "Organize office files",
      description: "Sort and label all office documents.",
      dueDate: new Date("2023-11-03"),
      isCompleted: true,
      priority: TaskPriority.MEDIUM,
    },

    {
      taskId: "7",
      title: "Prepare presentation",
      description: "Prepare slides for the upcoming team meeting.",
      dueDate: new Date("2023-11-04"),
      isCompleted: false,
      priority: TaskPriority.HIGH,
    },

    {
      taskId: "8",
      title: "Water plants",
      description: "Water all indoor and outdoor plants.",
      dueDate: new Date("2023-11-02"),
      isCompleted: false,
      priority: TaskPriority.LOW,
    },

    {
      taskId: "9",
      title: "Plan weekend getaway",
      description: "Organize a short weekend trip with friends.",
      dueDate: new Date("2023-11-06"),
      isCompleted: false,
      priority: TaskPriority.MEDIUM,
    },

    {
      taskId: "10",
      title: "Update software",
      description: "Update all applications and operating system on the laptop.",
      dueDate: new Date("2023-11-08"),
      isCompleted: true,
      priority: TaskPriority.LOW,
    },

    {
      taskId: "11",
      title: "Clean the garage",
      description: "Organize tools, boxes, and clear out unused items in the garage.",
      dueDate: new Date("2023-11-09"),
      isCompleted: false,
      priority: TaskPriority.MEDIUM,
    },

    {
      taskId: "12",
      title: "Prepare for client meeting",
      description: "Review client documents and create agenda for discussion.",
      dueDate: new Date("2023-11-10"),
      isCompleted: false,
      priority: TaskPriority.HIGH,
    },

    {
      taskId: "13",
      title: "Write blog post",
      description: "Draft and publish a new post on personal finance tips.",
      dueDate: new Date("2023-11-11"),
      isCompleted: false,
      priority: TaskPriority.LOW,
    },

    {
      taskId: "14",
      title: "Send birthday card",
      description: "Write and send a birthday card to Sarah.",
      dueDate: new Date("2023-11-12"),
      isCompleted: false,
      priority: TaskPriority.LOW,
    },
    
    {
      taskId: "15",
      title: "Research vacation destinations",
      description: "Explore and shortlist destinations for the winter vacation.",
      dueDate: new Date("2023-11-13"),
      isCompleted: false,
      priority: TaskPriority.MEDIUM,
    }
  ];
  

export {demoTasks};