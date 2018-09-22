package com.ms.dbpalio;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;

public class PalioAct extends Activity {
    private EditText input = null;
    private Button okay = null;
	
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // initializing the fields
        input = new EditText(this);
        input.setText("Enter text here ...");
        okay = new Button(this);
        okay.setText("Okay");
     
        // defining the layout in code instead of XML
    	LinearLayout layout = new LinearLayout(this);
    	layout.setOrientation(LinearLayout.VERTICAL);
    	layout.addView(input, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));
    	layout.addView(okay, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));
    
    	// activating the button
        okay.setOnClickListener(new ButtonOkayHandler());

    	// setting the view to our layout
    	setContentView(layout);
    }
    
    private void handleOkayButton() {
    	//setResult(Activity.RESULT_OK);
    	//finish();
    	Intent data = new Intent();
    	data.putExtra("input", input.getText().toString());
    	
    	setResult(Activity.RESULT_OK, data);
    	finish();
	}
}
