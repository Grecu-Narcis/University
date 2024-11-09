package com.example.taskplanner.main.repository

import com.example.taskplanner.main.domain.Task
import com.example.taskplanner.main.utils.demoTasks

class InMemoryRepository {
    private val tasks: MutableList<Task> = demoTasks.toMutableList()

    fun getTasks(): List<Task> {
        return this.tasks.toList()
    }

    fun addTask(taskToAdd: Task) {
        this.tasks.add(taskToAdd)
    }

    fun updateTask(taskToUpdate: Task) {
        this.tasks.forEachIndexed { index, task ->
            task.takeIf { it.taskId == taskToUpdate.taskId }?.let {
                this.tasks[index] = it.copy(
                    taskId = it.taskId,
                    title = taskToUpdate.title,
                    description = taskToUpdate.description,
                    dueDate = taskToUpdate.dueDate,
                    isCompleted = taskToUpdate.isCompleted,
                    priority = taskToUpdate.priority
                )
            }
        }
    }

    fun deleteTask(taskId: String) {
        this.tasks.removeIf { it.taskId == taskId }
    }
}