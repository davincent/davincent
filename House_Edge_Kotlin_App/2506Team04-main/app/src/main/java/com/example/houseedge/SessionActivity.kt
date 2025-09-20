package com.example.houseedge

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.gestures.detectHorizontalDragGestures
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.DrawerValue
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ModalBottomSheet
import androidx.compose.material3.ModalNavigationDrawer
import androidx.compose.material3.OutlinedButton
import androidx.compose.material3.Text
import androidx.compose.material3.rememberDrawerState
import androidx.compose.material3.rememberModalBottomSheetState
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.lerp
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlinx.coroutines.launch


class SessionActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val playerName = intent.getStringExtra("playerName") ?: "defaultPlayer"
        val tableName = intent.getStringExtra("tableName") ?: "defaultTable"
        val seatNumber = intent.getIntExtra("seatNumber", 0)
        val deckCount = intent.getIntExtra("deckCount", 0)

        setContent {
            CountScreen( playerName, tableName, seatNumber, deckCount)
        }
    }
}

@Composable
fun WinLossMenu( session : CountSession ,handList: MutableList<Hand>, onResult: () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxHeight()
            .width(250.dp)
            .background(Color.DarkGray)
            .padding(16.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        listOf("Win", "Loss", "Push").forEach { label ->
            OutlinedButton(
                onClick = {

                    session.result = label
                    handList.add(session.createHand())
                    session.updateHand()
                },

                modifier = Modifier

                    .fillMaxWidth()
                    .height(225.dp)
                    .padding(8.dp),

                border = BorderStroke(4.dp, Color.White),
                colors = ButtonDefaults.outlinedButtonColors(
                    contentColor = Color.White,
                    containerColor = Color(0xFF444444)


                )
            ) {
                Text(label, fontSize = 64.sp)

            }
        }
    }
}

// Design function for the buttons to update the count
@Composable
fun CountButtons(label: String, onClick: () -> Unit) {
    OutlinedButton(
        onClick = onClick,
        modifier = Modifier
            .fillMaxWidth()
            .height(240.dp)
            .padding(8.dp),
        border = BorderStroke(4.dp, Color.White),
        colors = ButtonDefaults.outlinedButtonColors(
            contentColor = Color.White,
            containerColor = Color(0xFF444444)
        )
    ) {
        Text(label, fontSize = 64.sp)
    }
}

// Numberpad within the wager popup menu
@Composable
fun NumberPad(input: String, onInputChanged: (String) -> Unit, onApply: () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .background(Color.Gray)
            .padding(8.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = input.ifEmpty { "0" },
            fontSize = 38.sp,
            modifier = Modifier.padding(bottom = 16.dp)
        )
        // Button list for the number pad
        val buttonRows = listOf(
            listOf("1", "2", "3"),
            listOf("4", "5", "6"),
            listOf("7", "8", "9"),
            listOf(".", "0", "Del")
        )
        buttonRows.forEach { row ->
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceEvenly
            ) {
                row.forEach { label ->
                    OutlinedButton(
                        onClick = {
                            when (label) {
                                "Del" -> {
                                    if (input.isNotEmpty()) {
                                        onInputChanged(input.dropLast(1))
                                    }
                                }

                                else -> {
                                    onInputChanged(input + label)
                                }
                            }
                        },
                        modifier = Modifier
                            .size(125.dp)
                            .padding(8.dp),
                        border = BorderStroke(4.dp, Color.White),
                        colors = ButtonDefaults.outlinedButtonColors(
                            contentColor = Color.White,
                            containerColor = Color(0xFF444444)
                        )
                    ) {
                        Text(label, fontSize = 38.sp)
                    }
                }
            }
        }
        Button(
            onClick = onApply,
            modifier = Modifier
                .fillMaxWidth()
                .padding(top = 16.dp)
                .height(50.dp)
        ) {
            Text("Set Wager", fontSize = 24.sp)
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun CountScreen(playerName: String, tableName: String, seatNumber: Int, deckCount: Int) {
    val drawerState = rememberDrawerState(initialValue = DrawerValue.Closed)
    val bottomSheetState = rememberModalBottomSheetState(skipPartiallyExpanded = true)
    val scope = rememberCoroutineScope()
    val session = remember { CountSession(playerName, tableName, seatNumber, deckCount) }
    var wagerInput by remember { mutableStateOf("") }
    var showBottomSheet by remember { mutableStateOf(false) }
    val context = LocalContext.current
    val handList = mutableListOf<Hand>()

    //handList.add(Hand(1,2,"Win", 100))

    val pdfLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.StartActivityForResult(),
        onResult = { result ->
            result.data?.data?.let { uri->

                val pdfDataLength = 700
                val pageHeight = handList.size * pdfDataLength
                createPDF(context, 816,pageHeight,1,handList,uri )


            }
        }
    )



    ModalNavigationDrawer(
        drawerState = drawerState,
        drawerContent = {

            WinLossMenu(session, handList)  {
                scope.launch { drawerState.close() }
            }
        }
    ) {
        Box(
            modifier = Modifier
                .fillMaxSize()
                .pointerInput(Unit) {
                    detectHorizontalDragGestures { _, dragAmount ->
                        if (dragAmount < 50) { // Positive indicates right swipe
                            scope.launch { drawerState.open() }
                        }
                    }
                }
        ) {

            Column(
                modifier = Modifier
                    .fillMaxSize()
                    .background(
                        brush = Brush.linearGradient(
                            colors = listOf(
                                Color(0xFFF50202),
                                Color(0xFFBD4747),
                                Color(0xFF6C6060),
                                Color(0xFF516B96),
                                Color(0xFF008ADF)
                            ),
                            start = Offset.Zero,
                            end = Offset.Infinite
                        )
                    )
                    .padding(top = 48.dp, start = 16.dp, end = 16.dp, bottom = 10.dp),
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                // Display for the Hand, Wager, and Count
                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(bottom = 32.dp),
                    horizontalArrangement = Arrangement.SpaceEvenly
                ) {
                    // Hand Count Box
                    Box(
                        modifier = Modifier
                            .background(Color.White)
                            .border(3.dp, Color.Black)
                            .padding(16.dp)
                    ) {
                        Text(text = "Hand: ${session.hand}", fontSize = 18.sp)
                    }
                    // Wager Box
                    Box(
                        modifier = Modifier
                            .background(Color.White)
                            .border(3.dp, Color.Black)
                            .padding(16.dp)
                            .clickable { showBottomSheet = true }
                    ) {
                        Text(text = "Wager: $${String.format("%.2f", session.wager.toDouble())}", fontSize = 18.sp)
                    }

                    val maxCount = 15
                    val fraction = (session.runningCount.toFloat()/ maxCount.toFloat()).coerceIn(0.0F,1.0F)
                    val interlopedButtonColor = lerp(Color(0xFF008ADF), Color(0xFFF50202), fraction)

                    // Count Box
                    Box(
                        modifier = Modifier
                            .background(interlopedButtonColor)
                            .border(3.dp, Color.Black)
                            .padding(16.dp)
                    ) {
                        Text(text = "Count: ${session.runningCount}", fontSize = 18.sp)
                    }
                }
                Box(
                    modifier = Modifier
                        .fillMaxSize(),
                    contentAlignment = Alignment.Center
                ) {
                    // Count Buttons to update the Count within the app screen
                    Column(
                        horizontalAlignment = Alignment.CenterHorizontally) {
                        CountButtons("+1") { session.updateRunningCount(session.runningCount + 1) }
                        CountButtons("0") {   }
                        CountButtons("-1") { session.updateRunningCount(session.runningCount - 1) }


                        //Export Button
                        Box(
                            modifier = Modifier
                                .background(Color.White)
                                .border(3.dp, Color.Black)
                                .padding(16.dp)
                                .clickable {
                                    scope.launch {
                                        Intent(Intent.ACTION_CREATE_DOCUMENT).apply {
                                            type = "application/pdf"
                                            putExtra(Intent.EXTRA_TITLE, "HouseEdgeData")
                                            pdfLauncher.launch(this)
                                        }


                                    }
                                }
                        ) {
                            Text(text = "Export", fontSize = 18.sp)
                        }
                    }

                }



            }

            // Bottom Sheet for the Wager input menu
            if (showBottomSheet) {
                ModalBottomSheet(
                    onDismissRequest = { showBottomSheet = false },
                    sheetState = bottomSheetState
                ) {
                    NumberPad(
                        input = wagerInput,
                        onInputChanged = { updated ->
                            wagerInput = updated
                        },
                        onApply = {
                            session.wager = wagerInput.toDoubleOrNull()?.toInt() ?: 0
                            showBottomSheet = false
                        }
                    )
                }
            }
        }
    }
}

