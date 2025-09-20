package com.example.houseedge

import android.content.Context
import android.graphics.Paint
import android.graphics.Typeface
import android.graphics.pdf.PdfDocument
import android.net.Uri
import androidx.core.content.ContextCompat


//LATER Create Hand class and change String to Hand
fun createPDF( context: Context,pageWidth: Int, pageHeight: Int, pageNumber :Int, handData:MutableList<Hand>, uri : Uri)
{
    val pdfCreator = PdfDocument()

    val pdfInfo = PdfDocument.PageInfo.Builder(pageWidth, pageHeight, pageNumber).create()

    val page = pdfCreator.startPage(pdfInfo)

    val canvas = page.canvas
    val text = Paint()
    text.setTypeface(Typeface.defaultFromStyle(Typeface.BOLD))
    text.setColor(ContextCompat.getColor(context,R.color.black))
    text.textSize = 30F
    text.textAlign = Paint.Align.CENTER

    canvas.drawText("House Edge",408F,100F,text)


    var y = 200F
    for (hand in handData) {
        canvas.drawText("Hand #" + hand.handNum.toString(), 408F,y,text)
        y = y +100F
        canvas.drawText("Count: " +hand.count.toString(), 408F,y,text)
        y = y +100F
        canvas.drawText("Result: "+hand.result, 408F,y,text)
        y = y +100F
        canvas.drawText("Wager: "+hand.wager.toString(), 408F,y,text)
        y = y +100F
    }

    pdfCreator.finishPage(page)




    context.contentResolver.openOutputStream(uri).use{
            outputStream -> pdfCreator.writeTo(outputStream)
    }


    pdfCreator.close()



}



