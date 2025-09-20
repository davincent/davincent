package com.example.houseedge.registrationSystem

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.houseedge.DetailActivity

class RegistrationActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            RegistrationScreen()
        }
    }
}

@Composable
fun RegistrationScreen() {
    var usernameText by remember { mutableStateOf("") }
    var emailText by remember { mutableStateOf("") }
    var passwordText by remember { mutableStateOf("") }
    var confirmPasswordText by remember { mutableStateOf("") }

    Scaffold(
        modifier = Modifier
            .fillMaxSize(),

        ) { innerPadding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding)
                .clip(
                    RoundedCornerShape(
                        topStart = 25.dp,
                        topEnd = 25.dp
                    )
                )
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
                )
                .padding(
                    horizontal = 16.dp,
                    vertical = 8.dp
                )
        ) {
            Spacer(modifier = Modifier.height(16.dp))

            LoginHeaderSection(
                modifier = Modifier.fillMaxWidth()
            )
            Spacer(modifier = Modifier.height(16.dp))

            LoginFormSection(
                usernameText = usernameText,
                onUsernameTextChange = { usernameText = it },
                emailText = emailText ,
                onEmailText = { emailText = it},
                passwordText = passwordText,
                onPasswordTextChange = { passwordText = it },
                confirmPasswordText = confirmPasswordText,
                onConfirmPasswordText = {confirmPasswordText = it},
                modifier = Modifier
                    .fillMaxSize()
            )
        }
    }
}

@Composable
fun LoginHeaderSection(modifier: Modifier = Modifier) {
    Column(
        modifier = modifier
    ) {
        Text(
            text = "Create Account",
            style = MaterialTheme.typography.displaySmall
        )
        Text(
            text = "Catch Those Card Counters!",
            style = MaterialTheme.typography.bodyLarge
        )
    }
}

@Composable
fun LoginFormSection(
    usernameText: String,
    onUsernameTextChange: (String) -> Unit,
    emailText: String,
    onEmailText: (String) -> Unit,
    passwordText: String,
    onPasswordTextChange: (String) -> Unit,
    confirmPasswordText: String,
    onConfirmPasswordText: (String) -> Unit,
    modifier: Modifier = Modifier
) {
    val context = LocalContext.current

    Box(
        modifier = modifier
    ) {
        Column(
            modifier = modifier
        ) {
            RegistrationTextField(
                text = usernameText,
                onValueChange = onUsernameTextChange,
                label = "UserName",
                hint = "john.doe",
                isInputSecret = false,
                modifier = Modifier
                    .fillMaxWidth()
            )
            Spacer(modifier = Modifier.height(16.dp))

            RegistrationTextField(
                text = emailText,
                onValueChange = onEmailText,
                label = "email",
                hint = "john.doe@example.com",
                isInputSecret = false,
                modifier = Modifier
                    .fillMaxWidth()
            )

            Spacer(modifier = Modifier.height(16.dp))

            RegistrationTextField(
                text = passwordText,
                onValueChange = onPasswordTextChange,
                label = "Password",
                hint = "Password",
                isInputSecret = true,
                modifier = Modifier
                    .fillMaxWidth()
            )
            Spacer(modifier = Modifier.height(16.dp))

            RegistrationTextField(
                text = confirmPasswordText,
                onValueChange = onConfirmPasswordText,
                label = "Password",
                hint = "Password",
                isInputSecret = true,
                modifier = Modifier
                    .fillMaxWidth()
            )

            Spacer(modifier = Modifier.height(28.dp))

            CreateAccountButton(
                text = "Create Account",
                onClick = {
                    val intent = Intent(context, DetailActivity::class.java)
                    context.startActivity(intent)
                },
                modifier = Modifier.fillMaxWidth()
            )
            Spacer(modifier = Modifier.height(28.dp))
        }
    }
}

@Preview(showBackground = true)
@Composable
fun RegistrationScreenPreview() {
    RegistrationScreen()
}