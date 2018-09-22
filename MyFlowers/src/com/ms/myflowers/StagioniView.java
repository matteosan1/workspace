package com.ms.myflowers;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
    
public class StagioniView extends View {
    //constructor 1 required for in-code creation
    public StagioniView(Context context) {
    	super(context);
    }

    //constructor 2 required for inflation from resource file
    public StagioniView(Context context, AttributeSet attr) {
    	super(context,attr);
    }

    //constructor 3 required for inflation from resource file
    public StagioniView(Context context, AttributeSet attr, int defaultStyles)  {
    	super(context, attr, defaultStyles);
    }

    @Override
    protected void onMeasure(int widthSpec, int heightSpec) {
    	//Log.v("TEST", Integer.toString(MeasureSpec.getSize(widthSpec)));
        int measuredWidth = 200;//MeasureSpec.getSize(widthSpec);
        int measuredHeight = 20;//MeasureSpec.getSize(heightSpec);

        setMeasuredDimension(measuredWidth, measuredHeight);
    }

    @Override
    protected void onDraw(Canvas canvas) {
		//get the size of your control based on last call to onMeasure
		int height = getMeasuredHeight();
		int width = getMeasuredWidth();

		// Now create a paint brush to draw your widget
		Paint mTextPaint = new Paint();
		mTextPaint.setColor(Color.GREEN);

		// set’s paint’s text size
		mTextPaint.setTextSize(40);
	 
		// Define the string you want to paint
		String displayText = "My First Widget";

		// Measure width of your text string
		Float textWidth = mTextPaint.measureText(displayText);

		//Find the center
		int px = width/2;
		int py = height/2;

		// Draw the string in the center of the control
		//canvas.drawText(displayText, px-textWidth/2, py, mTextPaint);
		canvas.drawRect(0, 0, 200, 10, mTextPaint);
     }
}
//<com.ms.myflowers.StagioniView
//	android:id="@+id/surface"
//	android:layout_width="fill_parent"
//	android:layout_height="fill_parent"/>     