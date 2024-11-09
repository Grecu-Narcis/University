package com.example.taskplanner.main.ui.screens

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import com.example.taskplanner.R
import com.example.taskplanner.main.ui.components.CustomButton
import com.example.taskplanner.main.ui.components.SearchBar
import com.example.taskplanner.main.ui.task.TaskList
import com.example.taskplanner.main.viewmodels.TasksViewModel

@Composable
fun HomeScreen(navController: NavController, tasksViewModel: TasksViewModel) {
    val tasksViewModelData by tasksViewModel.tasksData.collectAsState()

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
                "Tasks",
                fontWeight = FontWeight.Bold,
                textAlign = TextAlign.Center,
                fontSize = 24.sp,
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp, bottom = 8.dp)
            )

            SearchBar(
                tasksViewModel::updateFilterKey,
                searchQuery = tasksViewModelData.filterKey
            )
        }

        TaskList(
            modifier = Modifier.weight(1f),
            onEditTask = { navController.navigate("editTask/$it") },
            tasksViewModel = tasksViewModel
        )

        CustomButton(
            onClick = {
                navController.navigate("addTask")
            }, text = "Add task",
            containerColor = colorResource(R.color.main_button_color),
            modifier = Modifier.padding(top = 16.dp)
        )
    }
}