package com.ms.dbpalio;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
 
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
