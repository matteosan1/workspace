package com.ms.dbpalio.comparsa;

import com.ms.dbpalio.R;
import android.app.Activity;
import android.app.ListActivity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

import com.ms.dbpalio.dbHandler;
import com.ms.dbpalio.masgalano.MasDetailView;
import com.ms.dbpalio.masgalano.MasgalaniAct;
import com.ms.dbpalio.masgalano.MasgalaniDataSource;
import com.ms.dbpalio.masgalano.MasgalanoModel;

public class ComparsePerNomeAct extends ListActivity {
	
    private Button okay = null;
	private dbHandler db;
	private SQLiteDatabase database;
	private String nome;
	
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fantiniview);
        
        db = new dbHandler(this);
        database = db.getReadableDatabase();
		
        String q = "select data, ruolo from vittorie, comparse where nome = \"" + nome +"\"";
		Cursor cursor = database.rawQuery(q,  null);
		
		String[] columns = new String[] {"data", "ruolo"};
		int[] to = new int[] {R.id.anno, R.id.contrada};
		
		SimpleCursorAdapter mAdapter = new SimpleCursorAdapter(this, 
				R.layout.row, cursor, columns, to);
		setListAdapter(mAdapter);
      	
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
