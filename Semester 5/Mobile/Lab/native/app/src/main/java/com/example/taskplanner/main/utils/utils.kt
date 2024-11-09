package com.example.taskplanner.main.utils

import com.example.taskplanner.main.domain.Task
import com.example.taskplanner.main.domain.TaskPriority
import java.util.Date

val demoTasks = listOf(
    Task(
        taskId = "1",
        title = "Buy groceries",
        description = "Buy vegetables and fruits from the farmers' market.",
        dueDate = Date(System.currentTimeMillis() + 86400000), // Due tomorrow
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),
    Task(
        taskId = "2",
        title = "Finish homework",
        description = "Complete the math assignment and prepare for the physics test.",
        dueDate = Date(System.currentTimeMillis() + 172800000), // Due in 2 days
        isCompleted = false,
        priority = TaskPriority.MEDIUM
    ),
    Task(
        taskId = "3",
        title = "Workout",
        description = "Go for a run and do strength training.",
        dueDate = null, // No due date
        isCompleted = true,
        priority = TaskPriority.LOW
    ),
    Task(
        taskId = "4",
        title = "Read a book",
        description = "Finish reading 'The Great Gatsby'.",
        dueDate = Date(System.currentTimeMillis() + 604800000), // Due in 7 days
        isCompleted = false,
        priority = TaskPriority.MEDIUM
    ),
    Task(
        taskId = "5",
        title = "Plan weekend trip",
        description = "Research and plan activities for the upcoming weekend trip.",
        dueDate = Date(System.currentTimeMillis() + 259200000), // Due in 3 days
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),

    Task(
        taskId = "6",
        title = "Prepare project presentation",
        description = "Create slides and talking points for the upcoming project meeting.",
        dueDate = Date(System.currentTimeMillis() + 86400000), // Due in 1 day
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),
    Task(
        taskId = "7",
        title = "Grocery shopping",
        description = "Make a list and shop for weekly groceries.",
        dueDate = Date(System.currentTimeMillis() + 172800000), // Due in 2 days
        isCompleted = false,
        priority = TaskPriority.MEDIUM
    ),

    Task(
        taskId = "8",
        title = "Review code for team",
        description = "Review pull requests and provide feedback on code quality.",
        dueDate = Date(System.currentTimeMillis() + 432000000), // Due in 5 days
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),

    Task(
        taskId = "9",
        title = "Renew gym membership",
        description = "Check renewal options and complete payment for the gym.",
        dueDate = Date(System.currentTimeMillis() + 604800000), // Due in 7 days
        isCompleted = false,
        priority = TaskPriority.LOW
    ),

    Task(
        taskId = "10",
        title = "Write blog post",
        description = "Draft and publish a new blog post on a tech topic.",
        dueDate = Date(System.currentTimeMillis() + 259200000), // Due in 3 days
        isCompleted = false,
        priority = TaskPriority.MEDIUM
    ),

    Task(
        taskId = "11",
        title = "Team feedback session",
        description = "Prepare for and conduct feedback session with the team.",
        dueDate = Date(System.currentTimeMillis() + 345600000), // Due in 4 days
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),

    Task(
        taskId = "12",
        title = "Doctor’s appointment",
        description = "Routine check-up at the clinic.",
        dueDate = Date(System.currentTimeMillis() + 518400000), // Due in 6 days
        isCompleted = false,
        priority = TaskPriority.LOW
    ),

    Task(
        taskId = "13",
        title = "Update resume",
        description = "Revise and update resume with latest achievements.",
        dueDate = Date(System.currentTimeMillis() + 259200000), // Due in 3 days
        isCompleted = false,
        priority = TaskPriority.MEDIUM
    ),

    Task(
        taskId = "14",
        title = "Prepare tax documents",
        description = "Gather necessary documents and prepare for tax filing.",
        dueDate = Date(System.currentTimeMillis() + 1209600000), // Due in 14 days
        isCompleted = false,
        priority = TaskPriority.HIGH
    ),

    Task(
        taskId = "15",
        title = "Clean up workspace",
        description = "Organize and clean desk and surrounding area.",
        dueDate = Date(System.currentTimeMillis() + 86400000), // Due in 1 day
        isCompleted = false,
        priority = TaskPriority.LOW
    )
)