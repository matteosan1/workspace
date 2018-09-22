package com.ms.dbpalio.comparsa;

import android.app.Activity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.ms.dbpalio.R;
import com.ms.dbpalio.dbHandler;

public class ComparsePerAnnoAct extends Activity {
	
    private Button okay = null;
	private dbHandler db;
	private SQLiteDatabase database;
	
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.comdetailedview);
        
        Bundle bundle = this.getIntent().getExtras();
        String data = bundle.getString("combo");
        
        db = new dbHandler(this);
        database = db.getReadableDatabase();
        String q = "select nome, ruolo from comparse, vittorie where vittorie.data = \""+data+"\" and vittorie.indice = comparse._id;";
        Cursor cursor = database.rawQuery(q, null);
		cursor.moveToFirst();
		
		int alf = 0;
		int pp = 0;
		int pd = 0;
		int popolo = 0;
		
		while (cursor.isAfterLast() == false) {
			if (cursor.getString(1).equals("Tamburino")) {
				EditText et = (EditText) findViewById(R.id.tamburino);
				et.setText(cursor.getString(0));
			} 
			
			if (cursor.getString(1).equals("Duce")) {
				EditText et = (EditText) findViewById(R.id.duce);
				et.setText(cursor.getString(0));
			} 
		
			if (cursor.getString(1).equals("Figurin Maggiore")) {
				EditText et = (EditText) findViewById(R.id.paggiomaggiore);
				et.setText(cursor.getString(0));
			} 
		
			if (cursor.getString(1).equals("Palafreniere")) {
				EditText et = (EditText) findViewById(R.id.palafreniere);
				et.setText(cursor.getString(0));
			} 
		
			if (cursor.getString(1).equals("Soprallasso")) {
				EditText et = (EditText) findViewById(R.id.soprallasso);
				et.setText(cursor.getString(0));
			} 
		
			if (cursor.getString(1).equals("Vessillifero")) {
				EditText et = (EditText) findViewById(R.id.capopopolo);
				et.setText(cursor.getString(0));
			} 
		
			if (cursor.getString(1).equals("Alfiere")) {
				EditText et;
				if (alf == 0)
					et = (EditText) findViewById(R.id.alfiere1);
				else
					et = (EditText) findViewById(R.id.alfiere2);
				et.setText(cursor.getString(0));
				alf++;
			} 
		
			if (cursor.getString(1).equals("Uomo d\'Arme")) {
				EditText et;
				if (pd == 0)
					et = (EditText) findViewById(R.id.paggioduce1);
				else
					et = (EditText) findViewById(R.id.paggioduce2);
				et.setText(cursor.getString(0));
				pd++;
			} 
		
			if (cursor.getString(1).equals("Paggio Porta Insegna")) {
				EditText et;
				if (pp == 0)
					et = (EditText) findViewById(R.id.paggiopaggio1);
				else
					et = (EditText) findViewById(R.id.paggiopaggio2);
				et.setText(cursor.getString(0));
				pp++;
			} 
		

			if (cursor.getString(1).equals("Popolo")) {
				EditText et;
				if (popolo == 0)
					et = (EditText) findViewById(R.id.popolo1);
				else if (popolo == 1)
					et = (EditText) findViewById(R.id.popolo2);
				else if (popolo == 2)
					et = (EditText) findViewById(R.id.popolo3);
				else if (popolo == 3)
					et = (EditText) findViewById(R.id.popolo4);
				else if (popolo == 4)
					et = (EditText) findViewById(R.id.popolo5);
				else if (popolo == 5)
					et = (EditText) findViewById(R.id.popolo6);
				else
					et = (EditText) findViewById(R.id.popolo6);
				et.setText(cursor.getString(0));
				popolo++;
			} 
		
			cursor.moveToNext();
		}
		cursor.close();
		
		okay = (Button) findViewById(R.id.OK);
        okay.setOnClickListener(new ButtonOkayHandler());  
    }
    
    private void handleOkayButton() {
    	setResult(Activity.RESULT_OK);
    	finish();
    }
    
    @Override
    protected void onResume() {
    	database = db.getReadableDatabase();
    	super.onResume();
    }

    @Override
    protected void onPause() {
    	database.close();
    	super.onPause();
    }
}
