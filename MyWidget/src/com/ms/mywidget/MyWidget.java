package com.ms.mywidget;

import java.sql.Date;
import java.text.SimpleDateFormat;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;

import android.R;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.ComponentName;
import android.content.Context;
import android.text.format.DateFormat;
import android.widget.RemoteViews;

public class MyWidget extends AppWidgetProvider {

	@Override
	public void onUpdate(Context context, AppWidgetManager appWidgetManager, int[]  appWidgetIds) {
		Timer timer = new Timer();
		timer.scheduleAtFixedRate(new MyTime(context, appWidgetManager), 1, 1000);
	}
	
	private class MyTime extends TimerTask {
		RemoteViews remoteViews;
		AppWidgetManager appWidgetManager;
		ComponentName thisWidget;
		//DateFormat format = DateFormat.getTimeInstance(DateFormat.HOUR, Locale.getDefault());
		//DateFormat format = new DateFormat();
		
		public MyTime(Context context, AppWidgetManager appWidgetManager) {
			this.appWidgetManager = appWidgetManager;
			remoteViews = new RemoteViews(context.getPackageName(), R.layout.class.);
			thisWidget = new ComponentName(context, MyWidget.class);
		}
		
		@Override
		public void run() {
			remoteViews.setTextViewText(R.id.widget_textview, "Time = " + format.getformat(new Date()))));
			appWidgetManager.updateAppWidget(thisWidget, remoteViews);
		}
	}
}	
	
