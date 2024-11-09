package com.example.taskplanner.main.ui.components

import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.sp

@Composable
fun CustomButton(onClick: () -> Unit, text: String,
                 enabled: Boolean = true,
                 containerColor: Color = Color.Unspecified,
                 modifier: Modifier = Modifier) {
    Button(
        onClick = onClick, colors = ButtonDefaults.buttonColors(
            containerColor = containerColor
        ),
        enabled = enabled,
        modifier = modifier
    ) {
        Text(
            text,
            fontSize = 16.sp,
            fontWeight = FontWeight.Bold
        )
    }
}
