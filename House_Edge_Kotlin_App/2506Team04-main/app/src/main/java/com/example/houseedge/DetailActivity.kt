package com.example.houseedge

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.KeyboardArrowDown
import androidx.compose.material.icons.filled.KeyboardArrowUp
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.focus.FocusDirection
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.onGloballyPositioned
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.unit.toSize


class DetailActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            DetailScreen()
        }
    }
}

@Composable
fun DetailScreen() {

    Scaffold { innerPadding ->
        Box(
            modifier = Modifier
                .padding(innerPadding)
                .fillMaxSize()
                .background(
                    Brush.linearGradient(
                        listOf(
                            Color(0xFFF50202),
                            Color(0xFFBD4747),
                            Color(0xFF6C6060),
                            Color(0xFF516B96),
                            Color(0xFF008ADF)
                        )
                    )
                ),

            ) {
            Column(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(horizontal = 30.dp, vertical = 70.dp)

            ) {
                var player by remember { mutableStateOf("") }
                var table by remember { mutableStateOf("") }
                var seat by remember { mutableStateOf("") }
                var decks by remember { mutableStateOf("") }

                val focusManager = LocalFocusManager.current

                TextField(
                    value = player,
                    onValueChange = { player = it },
                    placeholder = {
                        Text(text = "Player Name", color = Color.Black)
                    },
                    supportingText = {
                        Text(text = "*required", color = Color.Black)
                    },
                    keyboardOptions = KeyboardOptions(
                        keyboardType = KeyboardType.Text,
                        imeAction = ImeAction.Next
                    ),
                    keyboardActions = KeyboardActions(
                        onNext = {
                            focusManager.moveFocus(FocusDirection.Down)
                        },
                    ),
                    singleLine = true,
                    modifier = Modifier.fillMaxWidth(1f)

                )
                Spacer(modifier = Modifier.height(16.dp))


                TextField(
                    value = table,
                    onValueChange = { table = it },
                    placeholder = {
                        Text(text = "Table Number", color = Color.Black)
                    },
                    supportingText = {
                        Text(text = "*required", color = Color.Black)
                    },
                    keyboardOptions = KeyboardOptions(
                        keyboardType = KeyboardType.Number,
                        imeAction = ImeAction.Next
                    ),
                    keyboardActions = KeyboardActions(
                        onNext = {
                            focusManager.moveFocus(FocusDirection.Down)
                        },
                    ),
                    singleLine = true,
                    modifier = Modifier.fillMaxWidth(1f)
                )
                Spacer(modifier = Modifier.height(16.dp))

                TextField(
                    value = seat,
                    onValueChange = { seat = it },
                    placeholder = {
                        Text(text = "Seat Number", color = Color.Black)
                    },
                    supportingText = {
                        Text(text = "*required", color = Color.Black)
                    },
                    keyboardOptions = KeyboardOptions(
                        keyboardType = KeyboardType.Number,
                        imeAction = ImeAction.Next
                    ),
                    keyboardActions = KeyboardActions(
                        onNext = {
                            focusManager.moveFocus(FocusDirection.Down)
                        },
                    ),
                    singleLine = true,
                    modifier = Modifier.fillMaxWidth(1f)
                )

                Spacer(modifier = Modifier.height(16.dp))

                TextField(
                    value = decks,
                    onValueChange = { decks = it },
                    placeholder = {
                        Text(text = "Number of Decks", color = Color.Black)
                    },
                    supportingText = {
                        Text(text = "*required", color = Color.Black)
                    },
                    keyboardOptions = KeyboardOptions(
                        keyboardType = KeyboardType.Number,
                        imeAction = ImeAction.Next
                    ),
                    keyboardActions = KeyboardActions(
                        onNext = {
                            focusManager.moveFocus(FocusDirection.Down)
                        },
                    ),
                    singleLine = true,
                    modifier = Modifier.fillMaxWidth(1f)
                )
                Spacer(modifier = Modifier.height(16.dp))

                var mExpanded by remember { mutableStateOf(false) }
                val mCountMethod = listOf("Hi-Low", "Ace-Five")
                var selectedText by remember { mutableStateOf("") }
                var textFieldSize by remember { mutableStateOf(Size.Zero) }
                val icon = if (mExpanded)
                    Icons.Filled.KeyboardArrowUp
                else
                    Icons.Filled.KeyboardArrowDown

                Column(
                    modifier = Modifier
                        .fillMaxWidth()
                ) {
                    TextField(
                        value = selectedText,
                        onValueChange = { selectedText = it },
                        modifier = Modifier
                            .fillMaxWidth(1f)
                            .onGloballyPositioned { layoutCoordinates ->
                                textFieldSize = layoutCoordinates.size.toSize()
                            },
                        placeholder = {
                            Text(text = "Count Method", color = Color.Black)
                        },
                        trailingIcon = {
                            Icon(
                                icon, "Count Methods",
                                Modifier.clickable { mExpanded = !mExpanded })
                        },
                        supportingText = {
                            Text(text = "*required", color = Color.Black)
                        }
                    )
                    DropdownMenu(
                        expanded = mExpanded,
                        onDismissRequest = { mExpanded = false },
                        modifier = Modifier
                            .width(with(LocalDensity.current) { textFieldSize.width.toDp() })
                    ) {
                        mCountMethod.forEach { placeholder ->
                            DropdownMenuItem(
                                text = { Text(text = placeholder) },
                                onClick = {
                                    selectedText = placeholder
                                    mExpanded = false
                                }
                            )
                        }
                    }
                }
            }
            StartCountButton()
        }
    }
}


@Composable
fun StartCountButton() {

    val context = LocalContext.current

    Box(
        modifier = Modifier
            .fillMaxSize()
            .padding(horizontal = 16.dp, vertical = 120.dp),
        contentAlignment = Alignment.BottomCenter
    ) {
        Button(
            onClick = {
                val intent = Intent(context, SessionActivity::class.java)
                context.startActivity(intent)
            },
            enabled = true,
            shape = ButtonDefaults.shape,
            border = BorderStroke(2.dp, color = Color.White),
            modifier = Modifier
                .size(400.dp, 150.dp),
            colors = ButtonDefaults.buttonColors(
                containerColor = Color(0xFF6C6060),
                contentColor = Color.Black,
            )
        ) {
            Column(
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.Bottom,
                modifier = Modifier
            ) {
                Text(
                    text = "START ",
                    fontSize = 50.sp,
                    fontWeight = FontWeight.Bold,
                    fontStyle = FontStyle.Italic
                )
                Text(
                    text = "COUNT",
                    fontSize = 50.sp,
                    fontWeight = FontWeight.Bold,
                    fontStyle = FontStyle.Italic
                )
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun DetailScreenPreview() {
    DetailScreen()
}