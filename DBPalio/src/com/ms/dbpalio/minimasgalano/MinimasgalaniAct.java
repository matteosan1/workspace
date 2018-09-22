package com.ms.dbpalio.minimasgalano;

import com.ms.dbpalio.R;
import com.ms.dbpalio.dbHandler;

import android.app.Activity;
import android.app.ListActivity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.SimpleCursorAdapter;

public class MinimasgalaniAct extends ListActivity {
	
    private Button okay = null;
	private dbHandler db;
	private SQLiteDatabase datasource;
			
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fantiniview);
        
        db = new dbHandler(this);
        datasource = db.getReadableDatabase();
		
        String q = "select * from minimasgalani;";
        Cursor cursor = datasource.rawQuery(q,  null);	 
		
		String[] columns = new String[] {"anno", "contrada"};
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
    	//Intent data = new Intent();
    	//data.putExtra("input", input.getText().toString());
    	
    	//setResult(Activity.RESULT_OK, data);
    	//finish();
	}
    
    @Override
    protected void onResume() {
    	datasource = db.getReadableDatabase();
    	super.onResume();
    }

    @Override
    protected void onPause() {
    	datasource.close();
    	super.onPause();
    }
}
