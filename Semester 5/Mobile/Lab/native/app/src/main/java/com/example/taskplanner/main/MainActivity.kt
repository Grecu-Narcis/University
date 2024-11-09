package com.example.taskplanner.main

import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import com.example.taskplanner.main.ui.screens.AddOrEditScreen
import com.example.taskplanner.main.ui.screens.HomeScreen
import com.example.taskplanner.main.viewmodels.TasksViewModel
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            App()
        }
    }
}

@Composable
fun App() {
    val navController = rememberNavController()
    val tasksViewModel: TasksViewModel = hiltViewModel()
    MaterialTheme {
        NavHost(navController = navController, startDestination = "main-screen") {
            composable("main-screen") {
                HomeScreen(
                    navController = navController,
                    tasksViewModel = tasksViewModel
                )
            }
            composable(
                route = "editTask/{taskId}",
                arguments = listOf(navArgument("taskId") { type = NavType.StringType })
            ) { backStackEntry ->
                AddOrEditScreen(
                    backStackEntry.arguments?.getString("taskId") ?: "",
                    navController = navController,
                    tasksViewModel = tasksViewModel
                )
            }

            composable(route = "addTask") {
                AddOrEditScreen(
                    navController = navController,
                    tasksViewModel = tasksViewModel
                )
            }
        }
    }
}



