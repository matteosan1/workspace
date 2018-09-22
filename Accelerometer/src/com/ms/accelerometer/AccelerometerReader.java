package com.ms.accelerometer;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.widget.TextView;
 
public class AccelerometerReader implements SensorEventListener {
    
	public float accX=0, accY=0, accZ=0;
	TextView tv1, tv2;
	
	public SensorManager mySensorManager; // used to acquire sensor access
    public Sensor accSensor; // accelerometer sensor object
    
    AccelerometerReader(Activity activity) {
    	tv1 = (TextView)activity.findViewById(R.id.acc);
    	tv2 = (TextView)activity.findViewById(R.id.accuracy);

    	// Set SensorManager and acquire a reference to accelerometer sensor
    	mySensorManager = (SensorManager)activity.getSystemService(Context.SENSOR_SERVICE);
    	List<Sensor> lista = mySensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
    	if (lista.size() > 0)
    		accSensor = lista.get(0);
    	else {
    		tv1.setText("Accelerometer not present !");
    		tv2.setText("");
    	}
    }
    
    // register current SensorEventListener
    void onResume() {
    	mySensorManager.registerListener(this, accSensor, SensorManager.SENSOR_DELAY_NORMAL);
    }
 
    // unregister current SensorEventListener
    void onStop() {
    	mySensorManager.unregisterListener(this);
    }
    
    // receives accuracy changes form sensor
    @Override
    public void onAccuracyChanged(Sensor sensor, int acc) {
    	//accuracy = acc;
    	//tv2.setText(Integer.toString(accuracy));
    }
 
    // receives sensor changes
    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
        	if (java.lang.Math.abs(event.values[0]) > accX)
        		accX = java.lang.Math.abs(event.values[0]);
        	if (java.lang.Math.abs(event.values[1]) > accY)
        		accY = java.lang.Math.abs(event.values[1]);
        	if (java.lang.Math.abs(event.values[2]) > accZ)
        		accZ = java.lang.Math.abs(event.values[2]);
        	
        	//accX = event.values[0];
        	//accY = event.values[1];
        	//accZ = event.values[2];
        	tv1.setText("(" + accX + ", " + accY + ", " + accZ + ")");
        }
    }
}