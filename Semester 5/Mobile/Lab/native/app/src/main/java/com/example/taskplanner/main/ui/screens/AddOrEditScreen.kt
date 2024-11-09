package com.example.taskplanner.main.ui.screens

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import com.example.taskplanner.R
import com.example.taskplanner.main.extensions.convertToFormat
import com.example.taskplanner.main.ui.components.CustomButton
import com.example.taskplanner.main.ui.components.CustomDatePickerDialog
import com.example.taskplanner.main.ui.components.CustomTextField
import com.example.taskplanner.main.ui.components.OptionPicker
import com.example.taskplanner.main.viewmodels.TasksViewModel

@Composable
fun AddOrEditScreen(
    taskId: String? = null,
    tasksViewModel: TasksViewModel,
    navController: NavController
) {
    val givenTask = tasksViewModel.findTaskById(taskId)
    var taskTitle by remember { mutableStateOf(givenTask?.title ?: "") }
    var taskDescription by remember { mutableStateOf(givenTask?.description ?: "") }
    var date by remember { mutableStateOf(givenTask?.dueDate?.convertToFormat() ?: "") }
    var showDatePicker by remember { mutableStateOf(false) }
    var taskPriority by remember { mutableStateOf(givenTask?.priority?.value ?: "Low") }

    Column(
        verticalArrangement = Arrangement.SpaceBetween,
        horizontalAlignment = Alignment.CenterHorizontally,
        modifier = Modifier
            .fillMaxWidth()
            .fillMaxHeight()
            .background(color = Color(0xFFF7FAFA))
            .padding(all = 16.dp)
    ) {
        // Header
        Column {
            Text(
                if (givenTask != null) "Edit task" else "Add task",
                fontWeight = FontWeight.Bold,
                textAlign = TextAlign.Center,
                fontSize = 24.sp,
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp, bottom = 16.dp)
            )
        }

        Column(
            verticalArrangement = Arrangement.spacedBy(16.dp),
            modifier = Modifier
                .fillMaxWidth()
                .weight(1f)
        ) {
            CustomTextField(
                value = taskTitle,
                onValueChanged = { taskTitle = it },
                placeHolderText = "Title"
            )

            CustomTextField(
                value = taskDescription,
                onValueChanged = { taskDescription = it },
                placeHolderText = "Description",
                modifier = Modifier
                    .height(144.dp)
            )

            Row(
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier.fillMaxWidth()
            ) {
                Column {
                    Text(
                        text = "Due Date",
                        color = colorResource(R.color.primary_text),
                        fontSize = 16.sp
                    )

                    if (date.isNotEmpty())
                        Text(
                            text = date,
                            color = colorResource(R.color.secondary_text),
                            fontSize = 14.sp
                        )
                }
                Icon(
                    painter = painterResource(id = R.drawable.date_picker),
                    contentDescription = "Search icon",
                    modifier = Modifier
                        .size(24.dp)
                        .clickable { showDatePicker = true },
                    tint = colorResource(R.color.primary_text)
                )
            }

            Row(
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier.fillMaxWidth()
            ) {
                Text(
                    text = "Priority",
                    color = colorResource(R.color.primary_text),
                    fontSize = 16.sp
                )

                OptionPicker(
                    onItemSelected = {
                        taskPriority = it
                    },
                    priority = givenTask?.priority?.value
                )
            }
        }

        if (showDatePicker) {
            CustomDatePickerDialog(
                onDateSelected = { date = it },
                onDismiss = { showDatePicker = false }
            )
        }

        CustomButton(
            onClick = {
                if (givenTask != null)
                    tasksViewModel.updateTask(
                        taskId = givenTask.taskId,
                        title = taskTitle,
                        description = taskDescription,
                        date = date,
                        isCompleted = false,
                        priority = taskPriority
                    )
                else
                    tasksViewModel.addTask(
                        title = taskTitle,
                        description = taskDescription,
                        date = date,
                        isCompleted = false,
                        priority = taskPriority
                    )

                navController.popBackStack()
            }, text = "Save",
            containerColor = colorResource(R.color.main_button_color),
            modifier = Modifier.padding(top = 16.dp)
        )
    }
}