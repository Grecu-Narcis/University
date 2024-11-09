package com.example.taskplanner.main.viewmodels

import androidx.lifecycle.ViewModel
import com.example.taskplanner.main.domain.Task
import com.example.taskplanner.main.domain.TaskPriority
import com.example.taskplanner.main.repository.InMemoryRepository
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import java.text.SimpleDateFormat
import java.util.Locale
import java.util.UUID
import javax.inject.Inject

@HiltViewModel
class TasksViewModel @Inject constructor(
    private val tasksRepository: InMemoryRepository
) : ViewModel() {
    private val _tasksData = MutableStateFlow(TasksViewModelData())
    val tasksData: StateFlow<TasksViewModelData> = _tasksData.asStateFlow()

    init {
        _tasksData.value = TasksViewModelData(
            this.tasksRepository.getTasks(), this.tasksRepository.getTasks()
        )
    }

    fun addTask(
        title: String, description: String, date: String, isCompleted: Boolean, priority: String
    ) {
        val taskToAdd = this.createTask(
            title = title,
            description = description,
            date = date,
            isCompleted = isCompleted,
            priority = priority
        )

        _tasksData.value = _tasksData.value.copy(
            tasks = _tasksData.value.tasks + taskToAdd,
            filteredTasks = _tasksData.value.tasks + taskToAdd,
            filterKey = ""
        )

        tasksRepository.addTask(taskToAdd)
    }

    fun updateTask(
        taskId: String,
        title: String,
        description: String,
        date: String,
        isCompleted: Boolean,
        priority: String
    ) {
        val taskToUpdate = this.createTask(
            taskId = taskId,
            title = title,
            description = description,
            date = date,
            isCompleted = isCompleted,
            priority = priority
        )

        val tasks = this._tasksData.value.tasks.map { if (it.taskId == taskId) taskToUpdate else it }

        _tasksData.value = _tasksData.value.copy(tasks = tasks, filteredTasks = tasks, filterKey = "")

        this.tasksRepository.updateTask(taskToUpdate)
    }

    fun deleteTask(taskId: String) {
        this._tasksData.value =
            this._tasksData.value.copy(
                tasks = this._tasksData.value.tasks.filter { it.taskId != taskId },
                filteredTasks = this._tasksData.value.filteredTasks.filter { it.taskId != taskId }
            )

        this.tasksRepository.deleteTask(taskId)
    }

    fun updateFilterKey(newFilterKey: String) {
        this._tasksData.value = this._tasksData.value.copy(filterKey = newFilterKey,
            filteredTasks = this._tasksData.value.tasks.filter { it.title.contains(newFilterKey) })
    }

    fun findTaskById(taskId: String?): Task? {
        return this._tasksData.value.tasks.find { it.taskId == taskId }
    }

    private fun convertStringToPriority(givenString: String): TaskPriority {
        when (givenString) {
            "Low" -> return TaskPriority.LOW
            "Medium" -> return TaskPriority.MEDIUM
            "High" -> return TaskPriority.HIGH
        }

        throw Exception("Priority invalid!")
    }

    private fun createTask(
        taskId: String? = null,
        title: String,
        description: String,
        date: String,
        isCompleted: Boolean,
        priority: String
    ): Task {
        val dueDate = if (date.isEmpty()) null else SimpleDateFormat(
            "dd/MM/yyyy", Locale.getDefault()
        ).parse(date)

        return Task(
            taskId = taskId ?: UUID.randomUUID().toString(),
            title = title,
            description = description,
            dueDate = dueDate,
            isCompleted = isCompleted,
            priority = convertStringToPriority(priority)
        )
    }
}