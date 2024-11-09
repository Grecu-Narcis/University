package com.example.taskplanner.main.ui.task

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.sp
import com.example.taskplanner.main.extensions.convertToFormat
import com.example.taskplanner.main.viewmodels.TasksViewModel

@Composable
fun TaskList(
    modifier: Modifier = Modifier,
    onEditTask: (String) -> Unit,
    tasksViewModel: TasksViewModel
) {
    val tasksViewModelData by tasksViewModel.tasksData.collectAsState()

    if (tasksViewModelData.filteredTasks.isEmpty())
        Column(
            verticalArrangement = Arrangement.Center,
            modifier = modifier
        ) {
            Text(
                "No task found! 🙁",
                fontSize = 24.sp
            )
        }
    else
        LazyColumn(modifier = modifier) {
            itemsIndexed(tasksViewModelData.filteredTasks) { _, task ->
                TaskCard(task = task,
                    onEditTask = onEditTask,
                    onStatusChange = {
                        tasksViewModel.updateTask(
                            taskId = task.taskId,
                            title = task.title,
                            description = task.description ?: "",
                            date = task.dueDate?.convertToFormat() ?: "",
                            isCompleted = !task.isCompleted,
                            priority = task.priority.value
                        )
                    },
                    onDeleteTask = { tasksViewModel.deleteTask(task.taskId) })
            }
        }
}