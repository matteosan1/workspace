package com.ms.dbpalio.cavallo;

import java.util.List;

import com.ms.dbpalio.R;
import com.ms.dbpalio.dbHandler;

import android.app.Activity;
import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class CavalliAct extends ListActivity {
	
	private CavalliDataSource datasource;
    private Button okay = null;
	private dbHandler db;
	
    private class ButtonOkayHandler implements View.OnClickListener {
    	public void onClick(View v)	{
    		handleOkayButton();	
    	}	
    }
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fantiniview);
        
        db = new dbHandler(this);
        datasource = new CavalliDataSource(db);
        datasource.open();
        List<CavalloModel> values = datasource.getAllCavalli();

        // Use the SimpleCursorAdapter to show the
        // elements in a ListView
        ArrayAdapter<CavalloModel> adapter = new ArrayAdapter<CavalloModel>
        	(this, android.R.layout.simple_list_item_1, values);
        setListAdapter(adapter);
      		
        ListView lv = (ListView) findViewById(android.R.id.list);
      	lv.setOnItemClickListener(showDetails);
      	
      	okay = (Button) findViewById(R.id.OK);
        okay.setOnClickListener(new ButtonOkayHandler());  
    }
    
    private OnItemClickListener showDetails = new OnItemClickListener() {
  	    public void onItemClick(AdapterView<?> parent, 
  	    		View view, int position, long id) {
  	    	
  	    	CavalloModel f = datasource.getCavallo(((TextView) view).getText().toString());
  	    	CavDetailView cD = new CavDetailView(CavalliAct.this);
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
