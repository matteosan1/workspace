package com.ms.firstproject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;

public class MyFirstProjectActivity extends ListActivity {
	
	//private FantinoDataSource datasource;
	private int written = 0;
	private int contentLength = 0;
	private int remoteVersion = -1;
	private Runnable openDB = null;
	private ProgressDialog m_ProgressDialog;
	public dbHandler db;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		int localVersion = checkLocalDb();
		
		if (!isNetworkAvailable(this)) {
			Toast toast = Toast.makeText(this, "Connessione di rete non disponibile\nImpossibile scaricare aggiornamenti.", Toast.LENGTH_LONG);
			toast.show();
			
			if (localVersion == -1) {
			    destroy();
			}
		} else {
			remoteVersion = checkRemoteDb();
			if (remoteVersion > localVersion) {
				openDB = new Runnable(){
					public void run() {
						getDB();
			        }
			    };
			        
			    Thread thread =  new Thread(null, openDB, "MagentoBackground");
			    thread.start();
			    //m_ProgressDialog = ProgressDialog.show(this,    
			    //		"Please wait...", "Retrieving data ...", true);
			    m_ProgressDialog = new ProgressDialog(this);
			    m_ProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			    m_ProgressDialog.setMessage("Loading DB...");
			    m_ProgressDialog.setCancelable(false);
			    m_ProgressDialog.show();
			}

			File f = new File("/data/data/com.ms.firstproject/databases/" + "palio_" + String.valueOf(localVersion) + ".db");
			f.delete();
	
			localVersion = remoteVersion;
			dbHandler.DBNAME = "palio_" + String.valueOf(localVersion) + ".db";
		}
		
		//db = new dbHandler(context);
		//datasource.open();
		//List<FantinoModel> values = datasource.getAllFantini();

		// Use the SimpleCursorAdapter to show the
		// elements in a ListView
		//ArrayAdapter<FantinoModel> adapter = new ArrayAdapter<FantinoModel>
		//	(this, android.R.layout.simple_list_item_1, values);
		//setListAdapter(adapter);
		
		//ListView lv = (ListView) findViewById(android.R.id.list);
		//lv.setOnItemClickListener(showDetails);
	}
	
	private Runnable returnRes = new Runnable() {

        public void run() {
            //if (written < contentLength){
                //m_adapter.notifyDataSetChanged();
                //for(int i=0;i<m_orders.size();i++)
                //	m_adapter.add(m_orders.get(i));
            	//m_ProgressDialog.setProgress((int)((double)written/(double)contentLength*10000.));
            //}
            m_ProgressDialog.dismiss();
            //m_adapter.notifyDataSetChanged();
        }
    };
    
    private void getDB() {
    	try {
    		// FIXME check file not found
    		URL url = new URL("http://sani.web.cern.ch/sani/palio_" + String.valueOf(remoteVersion) + ".db.txt");
		
    		URLConnection urlconn = url.openConnection();
    		contentLength = urlconn.getContentLength();
    		final int max = contentLength;
    		m_ProgressDialog.setMax(max);
    		//Log.i("DB", String.format("Download size %d", contentLength));
    		InputStream is = urlconn.getInputStream();
    		// Open the empty db as the output stream
    		OutputStream os = new FileOutputStream("/data/data/com.ms.firstproject/databases/" + "palio_" + String.valueOf(remoteVersion) + ".db");

			// transfer bytes from the inputfile to the outputfile
			byte[] buffer = new byte[1024 * 1000];
			written = 0;
			int length = 0;
			while (written < contentLength) {
				length = is.read(buffer);
				os.write(buffer, 0, length);
				written += length;
				//Thread.sleep(5000);
				final int prog = written;//(int)((double)written/(double)contentLength*100.);
				m_ProgressDialog.setProgress(prog);
				//Log.v("PD2", Integer.toString(prog));
				//final int currentprogress = written;     
				//Log.i("DB", String.format("progress %d", currentprogress));
			}

			os.flush();
			os.close();
			is.close();

			//Log.i("DB", "Download complete");
		} catch (Exception e) {
			Log.e("DB", "bad things", e);
		}
    	runOnUiThread(returnRes);
    }
    
	//private OnItemClickListener showDetails = new OnItemClickListener() {
	//    public void onItemClick(AdapterView<?> parent, 
	//    		View view, int position, long id) {
	    	
	//    	FantinoModel f = datasource.getFantino(((TextView) view).getText().toString());
	//    	FanDetailedView cD= new FanDetailedView(MyFirstProjectActivity.this);
	//    	cD.SetText(f);
	//    	cD.show();
	//    }
	//};


	// Will be called via the onClick attribute
	// of the buttons in main.xml
	public void onClick(View view) {
		@SuppressWarnings("unchecked")
		ArrayAdapter<FantinoModel> adapter = (ArrayAdapter<FantinoModel>) getListAdapter();
		//FantinoModel f = null;
		switch (view.getId()) {
		case R.id.add:
			//String[] comments = new String[] { "Cool", "Very nice", "Hate it" };
			//int nextInt = new Random().nextInt(3);
			// Save the new comment to the database
			//comment = datasource.createComment(comments[nextInt]);
			//adapter.add(comment);
			break;
		case R.id.delete:
			//if (getListAdapter().getCount() > 0) {
			//	comment = (Comment) getListAdapter().getItem(0);
			//	datasource.deleteComment(comment);
			//	adapter.remove(comment);
			//}
			break;
		}
		adapter.notifyDataSetChanged();
	}

	@Override
	protected void onResume() {
		//datasource.open();
		super.onResume();
	}

	@Override
	protected void onPause() {
		//datasource.close();
		super.onPause();
	}
	
	public void destroy() {
		AlertDialog alertDialog = new AlertDialog.Builder(this).create();  
	    alertDialog.setTitle("DataBase Alert");  
	    alertDialog.setMessage("Il database del Palio non e` disponibile !");  
	    alertDialog.setButton("OK", new DialogInterface.OnClickListener() {  
	      public void onClick(DialogInterface dialog, int which) {
	    	  //Log.v("DB", Integer.toString(which));
	    	  if (which == -1) {
	    		  File f = new File("/data/data/com.ms.firstproject/databases/palio_0.db");
	    		  f.delete();
	    		  finish();
	    	  }
	    	  return;	
	      }
	    }); 
	    alertDialog.show();
	}
	
	private int checkLocalDb() {
		int currentDbVersion = -1;
		// FIXME generalizzare il path sotto
		File dir = new File("/data/data/com.ms.firstproject/databases");
		FilenameFilter filter = new FilenameFilter() {
		    public boolean accept(File dir, String name) {
		        return name.endsWith(".db");
		    }
		};
		
		String[] children = dir.list(filter);
		
		if (children.length == 0) {
			return -1;
		} else {	
			Pattern p = Pattern.compile("palio_([0-9]+).db");
            Matcher m = p.matcher(children[0]); 
            boolean result = m.find();
            if (result)
            	currentDbVersion = Integer.parseInt(m.group(1));
		}
		
		return currentDbVersion;
	}
	
	public boolean isNetworkAvailable(Context context) {
		
		ConnectivityManager conMan = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
		boolean connection = false;
		State mobile = conMan.getNetworkInfo(ConnectivityManager.TYPE_MOBILE).getState();
		State wifi = conMan.getNetworkInfo(ConnectivityManager.TYPE_WIFI).getState();
		if (wifi == NetworkInfo.State.CONNECTED || wifi == NetworkInfo.State.CONNECTING) {
		    connection = true;
		}
		
		if (mobile == NetworkInfo.State.CONNECTED || wifi == NetworkInfo.State.CONNECTING) {
		    connection = true;
		}
		
		return connection;
	}

	private int checkRemoteDb() {
		int remoteVersion = -1;
		
		try {
			//URL url = new URL("http://home.cern.ch//sani//paliodb.txt");
			URL url = new URL("http://dl.dropbox.com/u/15362671/paliodb.txt");
			URLConnection ucon = url.openConnection();
			BufferedReader in = new BufferedReader(new InputStreamReader(ucon.getInputStream()));
			
			String inputLine;
			String tot = "";
			while ((inputLine = in.readLine()) != null) {
				tot = tot + inputLine;
			}

			in.close();
			remoteVersion = Integer.parseInt(tot);

		} catch (MalformedURLException e) {
			Log.v("DB1", e.getMessage());
		} catch (IOException e) {
			Log.v("DB2", e.getMessage());
		}
		
		return remoteVersion;
	}
	
}