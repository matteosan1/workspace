package com.ms.notification;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class NotificationActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		Button buttonStartService = (Button)findViewById(R.id.startservice);
		Button buttonStopService = (Button)findViewById(R.id.stopservice);
  
		buttonStartService.setOnClickListener(new Button.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent(NotificationActivity.this, com.ms.notification.NotifyService.class);
				NotificationActivity.this.startService(intent);
			}
		});
  
		buttonStopService.setOnClickListener(new Button.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent();
				intent.setAction(NotifyService.ACTION);
				intent.putExtra("RQS", NotifyService.RQS_STOP_SERVICE);
				sendBroadcast(intent);
			}
		});
  
	}
}
