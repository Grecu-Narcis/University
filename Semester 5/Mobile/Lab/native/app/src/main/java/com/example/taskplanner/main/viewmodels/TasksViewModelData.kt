package com.example.taskplanner.main.viewmodels

import com.example.taskplanner.main.domain.Task

data class TasksViewModelData(
    val tasks: List<Task> = emptyList(),
    val filteredTasks: List<Task> = emptyList(),
    val filterKey: String = ""
)