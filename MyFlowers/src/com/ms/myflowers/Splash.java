package com.ms.myflowers;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.MotionEvent;

public class Splash extends Activity {
	
	protected boolean _active = true;
	protected int _splashTime = 5000;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.splash);
	 
	    // thread for displaying the SplashScreen
	    Thread splashTread = new Thread() {
	        @Override
	        public void run() {
	        	try {
	        		int waited = 0;
	        		while(_active && (waited < _splashTime)) {
	        			sleep(100);
	        			if(_active) {
	        				waited += 100;
	        			}
	        		}
	                
	        		finish();
	        		startActivity(new Intent("com.ms.myflowers.MyFlowersActivity"));
	        		return;
	        	} catch (Exception e) {
	        	}
	        }
	    };
	    splashTread.start();
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
	    if (event.getAction() == MotionEvent.ACTION_DOWN) {
	        _active = false;
	    }
	    return true;
	}
}
