package com.ms.dbpalio.comparsa;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

import com.ms.dbpalio.R;
import com.ms.dbpalio.dbHandler;

public class ComparseAct extends Activity {
	
    private Button okay = null;
	private dbHandler db;
	static public SQLiteDatabase database;
	
	public class CustomOnItemSelectedListener implements OnItemSelectedListener {
		private int i = 0;
		public void onItemSelected(AdapterView<?> parent, View view, int pos,long id) {
			if (i==0) {
				i++;
				return;
			}
			
			startActivityPerAnno(parent.getItemAtPosition(pos).toString());
		}
		 
		@Override
		public void onNothingSelected(AdapterView<?> arg0) 
		{}
	}
	
	private class ButtonCercaHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleCercaButton();	
    	}	
    }
	
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.comparseview);
        
        db = new dbHandler(this);
        database = db.getReadableDatabase();
        
        String q = "select distinct data from vittorie, comparse where vittorie.indice = comparse._id order by data desc;"; 		
		Cursor cursor = database.rawQuery(q,  null);
		List<String> list = new ArrayList<String>();
		cursor.moveToFirst();
		while (cursor.isAfterLast() == false) {
			list.add(cursor.getString(0));
			cursor.moveToNext();
		}
		cursor.close();
		
		Spinner sp = (Spinner) findViewById(R.id.spinner);
		sp.setOnItemSelectedListener(new CustomOnItemSelectedListener());
		ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this,
					android.R.layout.simple_spinner_item, list);
		dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		sp.setAdapter(dataAdapter);
      		
		Button cerca = (Button) findViewById(R.id.cerca);
		cerca.setOnClickListener(new ButtonCercaHandler());
		
      	okay = (Button) findViewById(R.id.OK);
        okay.setOnClickListener(new ButtonOkayHandler());  
    }
    
    private void startActivityPerAnno(String s) {
		Bundle bundle = new Bundle();
		bundle.putString("textedit", "");
		bundle.putString("combo", s);
		Intent i = new Intent(this, ComparsePerAnnoAct.class);
		i.putExtras(bundle);
		startActivityForResult(i, 0);
    }
    private void handleCercaButton() {
    	EditText te = (EditText) findViewById(R.id.comp_nome);
		Bundle bundle = new Bundle();
		bundle.putString("textedit", te.getText().toString());
		bundle.putString("combo", "");
		Intent newIntent = new Intent(this, ComparsePerNomeAct.class);
		newIntent.putExtras(bundle);
		startActivityForResult(newIntent, 0);
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
