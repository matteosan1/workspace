package com.ms.dbpalio;

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
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.ms.dbpalio.cavallo.CavalliAct;
import com.ms.dbpalio.comparsa.ComparseAct;
import com.ms.dbpalio.fantino.FantiniAct;
import com.ms.dbpalio.masgalano.MasgalaniAct;
import com.ms.dbpalio.minimasgalano.MinimasgalaniAct;

public class DBPalioActivity extends Activity {
	private int written = 0;
	private int contentLength = 0;
	private int remoteVersion = -1;
	private Runnable openDB = null;
	private ProgressDialog m_ProgressDialog;
	//static public dbHandler db;
	
	private int INPUT_REQUEST = 0;
	private List<Button> buttons = new ArrayList<Button>();
	
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
			        
			    Thread thread =  new Thread(null, openDB, "");
			    thread.start();
			    //m_ProgressDialog = ProgressDialog.show(this,    
			    //		"Please wait...", "Retrieving data ...", true);
			    m_ProgressDialog = new ProgressDialog(this);
			    m_ProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			    m_ProgressDialog.setMessage("Loading DB...");
			    m_ProgressDialog.setCancelable(false);
			    m_ProgressDialog.show();
			    
				File f = new File("/data/data/com.ms.dbpalio/databases/" + "palio_" + String.valueOf(localVersion) + ".db");
				f.delete();
		
				localVersion = remoteVersion;		
			}
			
			dbHandler.DBNAME = "palio_" + String.valueOf(localVersion) + ".db";
		}
		
		buttons.add((Button) findViewById(R.id.cavalli));
		buttons.add((Button) findViewById(R.id.fantini));
		buttons.add((Button) findViewById(R.id.palio));
		buttons.add((Button) findViewById(R.id.comparse));
		buttons.add((Button) findViewById(R.id.masgalani));
		buttons.add((Button) findViewById(R.id.minimasgalani));
		
		// activating the button
		for (int i=0; i<buttons.size(); i++)
			buttons.get(i).setOnClickListener(new ButtonHandler());
	}

	private class ButtonHandler implements View.OnClickListener {
		public void onClick(View v) {
			handleButtonClick(v.getId());
		}
	}

	private void handleButtonClick(int id) {
		//startActivity(new Intent(this, SecondAct.class));
		switch (id) {
			case R.id.cavalli:
				startActivityForResult(new Intent(this, CavalliAct.class), INPUT_REQUEST);
				break;
			case R.id.fantini:
				startActivityForResult(new Intent(this, FantiniAct.class), INPUT_REQUEST);
				break;
			case R.id.palio:
				startActivityForResult(new Intent(this, PalioAct.class), INPUT_REQUEST);
				break;
			case R.id.comparse:
				startActivityForResult(new Intent(this, ComparseAct.class), INPUT_REQUEST);
				break;
			case R.id.masgalani:
				startActivityForResult(new Intent(this, MasgalaniAct.class), INPUT_REQUEST);
				break;
			case R.id.minimasgalani:
				startActivityForResult(new Intent(this, MinimasgalaniAct.class), INPUT_REQUEST);
				break;
			default:
				break;
		}
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data); 	
		//if (resultCode == Activity.RESULT_CANCELED) 
		//	Toast.makeText(this, "activity canceled", Toast.LENGTH_SHORT).show(); 
		//else if (resultCode == Activity.RESULT_OK) 
		//	Toast.makeText(this, "activity ok", Toast.LENGTH_SHORT).show(); 
	}
	
	private Runnable returnRes = new Runnable() {
        public void run() {
        	m_ProgressDialog.dismiss();
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
    		OutputStream os = new FileOutputStream("/data/data/com.ms.dbpalio/databases/" + "palio_" + String.valueOf(remoteVersion) + ".db");

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
    
	public void destroy() {
		AlertDialog alertDialog = new AlertDialog.Builder(this).create();  
	    alertDialog.setTitle("DataBase Alert");  
	    alertDialog.setMessage("Il database del Palio non e` disponibile !");  
	    alertDialog.setButton("OK", new DialogInterface.OnClickListener() {  
	      public void onClick(DialogInterface dialog, int which) {
	    	  //Log.v("DB", Integer.toString(which));
	    	  if (which == -1) {
	    		  File f = new File("/data/data/com.ms.dbpalio/databases/palio_0.db");
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
		File dir = new File("/data/data/com.ms.dbpalio/databases");
		if (!dir.isDirectory())
			dir.mkdir();
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
			URL url = new URL("http://home.cern.ch/sani/paliodb.txt");
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
	
    @Override
    protected void onResume() {
            super.onResume();
    }

    @Override
    protected void onPause() {
            super.onPause();
    }
}