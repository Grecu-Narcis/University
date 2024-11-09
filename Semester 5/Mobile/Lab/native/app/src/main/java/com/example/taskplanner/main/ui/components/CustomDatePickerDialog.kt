package com.example.taskplanner.main.ui.components

import androidx.compose.material3.DatePicker
import androidx.compose.material3.DatePickerDefaults
import androidx.compose.material3.DatePickerDialog
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.rememberDatePickerState
import androidx.compose.runtime.Composable
import androidx.compose.ui.res.colorResource
import com.example.taskplanner.R
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun CustomDatePickerDialog(onDateSelected: (String) -> Unit, onDismiss: () -> Unit) {
    val datePickerState = rememberDatePickerState()

    val selectedDate = datePickerState.selectedDateMillis?.let {
        convertMillisToDate(it)
    } ?: ""

    val isDateSelected = datePickerState.selectedDateMillis != null

    DatePickerDialog(
        onDismissRequest = { onDismiss() },
        confirmButton = {
            CustomButton(
                onClick = {
                    onDateSelected(selectedDate)
                    onDismiss()
                },
                text = "Ok",
                enabled = isDateSelected,
                containerColor = colorResource(R.color.main_button_color)
            )
        },
        dismissButton = {
            CustomButton(onClick = {
                onDismiss()
            }, text = "Cancel",
                containerColor = colorResource(R.color.red)
            )
        },
        colors = DatePickerDefaults.colors(
            selectedDayContainerColor = colorResource(R.color.main_button_color),
            todayDateBorderColor = colorResource(R.color.main_button_color)
        )
    ) {
        DatePicker(
            state = datePickerState
        )
    }
}

private fun convertMillisToDate(millis: Long): String {
    val formatter = SimpleDateFormat("dd/MM/yyyy", Locale.getDefault())
    return formatter.format(Date(millis))
}