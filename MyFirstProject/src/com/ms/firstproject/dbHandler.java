package com.ms.firstproject;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import org.apache.http.util.ByteArrayBuffer;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.util.Log;
import android.widget.Toast;
 
public class dbHandler extends SQLiteOpenHelper {
	
	public static String DBNAME = "palio_0.db";
	public dbHandler myDBHelper;
	public SQLiteDatabase myDB;
	public final Context myContext;
	
	public dbHandler(Context context) {
		super(context, DBNAME, null, 1);
		this.myContext = context;
	}
 
	@Override
	public void onCreate(SQLiteDatabase db) 
	{}
 
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) 
	{}
}
