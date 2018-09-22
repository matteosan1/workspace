package com.ms.accelerometer;

import android.app.Activity;
import android.os.Bundle;

public class AccelerometerActivity extends Activity {
	
	private AccelerometerReader accReader;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //float[] values = new float[] { 2.0f,1.5f, 2.5f, 1.0f , 3.0f };
		//String[] verlabels = new String[] { "great", "ok", "bad" };
		//String[] horlabels = new String[] { "today", "tomorrow", "next week", "next month" };
		//GraphView graphView = new GraphView(this, values, "GraphViewDemo",horlabels, verlabels, GraphView.LINE);
        setContentView(R.layout.main);
		//setContentView(graphView);
        accReader = new AccelerometerReader(this);
    }
    
    // register current SensorEventListener
    @Override
    protected void onResume() {
    	super.onResume();
    	accReader.onResume();
    }
 
    // unregister current SensorEventListener
    @Override
    protected void onStop() {
    	accReader.onStop();
    	super.onStop();
    }
}