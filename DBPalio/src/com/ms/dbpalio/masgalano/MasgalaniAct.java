package com.ms.dbpalio.masgalano;

import com.ms.dbpalio.R;
import com.ms.dbpalio.dbHandler;

import android.app.Activity;
import android.app.ListActivity;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

public class MasgalaniAct extends ListActivity {
	
	private MasgalaniDataSource datasource;
    private Button okay = null;
	private dbHandler db;
	private Cursor cursor;
	//private SQLiteDatabase database;
			
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fantiniview);
        
        db = new dbHandler(this);
        datasource = new MasgalaniDataSource(db);
        datasource.open();
		
		cursor = datasource.getMasgalani();
		String[] columns = new String[] {"data", "contrada", "organizzatore"};
		int[] to = new int[] {R.id.anno, R.id.contrada, R.id.cavallo};
		
		SimpleCursorAdapter mAdapter = new SimpleCursorAdapter(this, 
				R.layout.row, cursor, columns, to);
		setListAdapter(mAdapter);
      	
		ListView lv = (ListView) findViewById(android.R.id.list);
      	lv.setOnItemClickListener(showDetails);
      	
      	okay = (Button) findViewById(R.id.OK);
        okay.setOnClickListener(new ButtonOkayHandler());  
    }
    
    private OnItemClickListener showDetails = new OnItemClickListener() {
  	    public void onItemClick(AdapterView<?> parent, 
  	    		View view, int position, long id) {
  	    	cursor.moveToPosition(position);
  	    	MasgalanoModel f = datasource.getMasgalano(cursor.getInt(0));
  	    	MasDetailView cD = new MasDetailView(MasgalaniAct.this);
  	    	cD.SetText(f);
  	    	cD.show();
  	    }
  	};

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
    	datasource.open();
    	super.onResume();
    }

    @Override
    protected void onPause() {
    	datasource.close();
    	super.onPause();
    }
}
