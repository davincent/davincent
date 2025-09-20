package com.example.houseedge

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.Font
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.houseedge.ui.theme.HouseEdgeTheme
import com.example.houseedge.loginSystem.LoginActivity


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            HouseEdgeTheme {
                Scaffold(
                    modifier = Modifier
                        .fillMaxSize()
                )
                { innerPadding ->
                    HouseEdgeLogo(
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
                            )
                    )
                    StartButton()
                }
            }
        }
    }
}
//Alignment = Cross Axis (Row = Vertical, Column = Horizontal)
//Arrangement = Main Axis (Row = Horizontal, Column = Vertical)
//RowAlignment: Top, CenterVertically, Bottom
//RowArrangement: Start, Center, End, SpaceBetween, SpaceAround, SpaceEvenly,
//Absolute.Left, Absolute.Right, Absolute.Center
//Absolute.SpaceBetween, Absolute.SpaceAround, Absolute.SpaceEvenly
@Composable
fun StartButton() {

    val context = LocalContext.current

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Button(
            onClick = {
                val intent = Intent(context, LoginActivity::class.java)
                context.startActivity(intent)
            },
            enabled = true,
            shape = ButtonDefaults.shape,
            border = BorderStroke(2.dp,color = Color.White),
            modifier = Modifier
                .size(400.dp, 150.dp),
            colors = ButtonDefaults.buttonColors(
                containerColor = Color(0xFF6C6060),
                contentColor = Color.Black,

                )
        ) {
            Column(
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.Top,
                modifier = Modifier
            ) {
                Text(
                    text = "START ",
                    fontSize = 50.sp,
                    fontWeight = FontWeight.Bold,
                    fontStyle = FontStyle.Italic
                )
                Text(
                    text = "SESSION",
                    fontSize = 50.sp,
                    fontWeight = FontWeight.Bold,
                    fontStyle = FontStyle.Italic
                )


            }
        }
    }
}

@Composable
fun HouseEdgeLogo(modifier: Modifier = Modifier) {
    val fontFamily = FontFamily(
        Font(R.font.lexend_thin, FontWeight.Thin),
        Font(R.font.lexend_extralight, FontWeight.ExtraLight),
        Font(R.font.lexend_light, FontWeight.Light),
        Font(R.font.lexend_regular, FontWeight.Normal),
        Font(R.font.lexend_medium, FontWeight.Medium),
        Font(R.font.lexend_semibold, FontWeight.SemiBold),
        Font(R.font.lexend_bold, FontWeight.Bold),
        Font(R.font.lexend_extrabold, FontWeight.ExtraBold),
        Font(R.font.lexend_black, FontWeight.Black)
    )

    Column(
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally,
        modifier = modifier
            .padding(41.dp)
    ) {
        Text(
            text = "HOUSE",
            color = Color.LightGray,
            fontSize = 100.sp,
            fontFamily = fontFamily,
            fontWeight = FontWeight.Bold,
            fontStyle = FontStyle.Italic
        )
        Text(
            text = "EDGE",
            color = Color.LightGray,
            fontSize = 110.sp,
            fontFamily = fontFamily,
            fontWeight = FontWeight.Bold,
            fontStyle = FontStyle.Italic
        )
    }
}


