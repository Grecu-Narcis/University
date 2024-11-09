package com.example.taskplanner.main.ui.task

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentWidth
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Checkbox
import androidx.compose.material3.CheckboxDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.taskplanner.R
import com.example.taskplanner.main.domain.Task

const val maxLength = 25

@Composable
fun TaskCard(
    task: Task,
    onStatusChange: (String) -> Unit,
    onEditTask: (String) -> Unit,
    onDeleteTask: (String) -> Unit
) {
    var showDialog by remember { mutableStateOf(false) }


    Row(
        verticalAlignment = Alignment.CenterVertically,
        horizontalArrangement = Arrangement.SpaceBetween,
        modifier = Modifier
            .fillMaxWidth()
            .padding(top = 8.dp, end = 8.dp, bottom = 8.dp)
    ) {
        Row(
            verticalAlignment = Alignment.CenterVertically,
            modifier = Modifier
                .wrapContentWidth()
                .weight(1f)
        ) {
            Checkbox(
                checked = task.isCompleted,
                onCheckedChange = { onStatusChange(task.taskId) },
                modifier = Modifier
                    .clip(RoundedCornerShape(8.dp))
                    .padding(start = 0.dp),
                colors = CheckboxDefaults.colors(
                    checkedColor = colorResource(R.color.main_button_color)
                )
            )

            Text(
                text = if (task.title.length > maxLength) task.title.take(maxLength) + "..." else task.title,
                color = colorResource(R.color.primary_text),
                fontSize = 16.sp,
                modifier = Modifier
                    .padding(start = 0.dp)
                    .weight(1f)
            )
        }

        Row(
            verticalAlignment = Alignment.CenterVertically
        ) {
            Button(
                onClick = { onEditTask(task.taskId) },
                colors = ButtonDefaults.buttonColors(
                    containerColor = colorResource(R.color.main_button_color)
                ),
                contentPadding = PaddingValues(horizontal = 0.dp)
            ) {
                Text(
                    text = "Edit",
                    color = Color.White,
                    fontSize = 14.sp,
                    fontWeight = FontWeight.Bold
                )
            }

            Icon(
                painter = painterResource(id = R.drawable.trash),
                contentDescription = "Trash can icon",
                tint = colorResource(R.color.primary_text),
                modifier = Modifier
                    .padding(start = 12.dp)
                    .clickable {
                        showDialog = true
                    }

            )
        }
    }

    if (showDialog) {
        AlertDialog(
            onDismissRequest = { showDialog = false },
            title = { Text("Delete confirmation") },
            text = { Text("Are you sure you want to remove this task?") },
            confirmButton = {
                TextButton(
                    onClick = {
                        onDeleteTask(task.taskId)
                        showDialog = false
                    }
                ) {
                    Text("Delete")
                }
            },
            dismissButton = {
                TextButton(
                    onClick = { showDialog = false }
                ) {
                    Text("Cancel")
                }
            }
        )
    }
}