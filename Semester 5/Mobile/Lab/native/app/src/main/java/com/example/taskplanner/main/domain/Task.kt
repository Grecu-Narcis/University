package com.example.taskplanner.main.domain

import java.util.Date

data class Task(
    val taskId: String,
    val title: String,
    val description: String?,
    val dueDate: Date?,
    val isCompleted: Boolean,
    val priority: TaskPriority
)