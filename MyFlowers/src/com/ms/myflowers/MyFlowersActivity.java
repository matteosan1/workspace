package com.ms.myflowers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.res.TypedArray;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.ExifInterface;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MyFlowersActivity extends Activity {
    
	private dbHandler dbH;
	private SQLiteDatabase database;
	ImageView imageView;
	Gallery ga;
	TextView tv;
	private String[] files;
	private List<String> nome = new ArrayList<String>();
    private List<String> file = new ArrayList<String>();
    private String[] pics;
    private Integer binaryChoice = 255;
    private Runnable openDB = null;
	private ProgressDialog m_ProgressDialog;
	private Button addPhoto;
	private static final int SELECT_PHOTO = 100;
	
	private class ButtonHandler implements View.OnClickListener {
        public void onClick(View v)     {
                handleButton();     
        }       
    }
	
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        update(false);       
        
        ga = (Gallery)findViewById(R.id.Gallery01);
        ga.setAdapter(new ImageAdapter(this));
        
        tv = (TextView) findViewById(R.id.textView1);
        addPhoto = (Button) findViewById(R.id.button1);
        addPhoto.setOnClickListener(new ButtonHandler());
        
        imageView = (ImageView)findViewById(R.id.ImageView01);
        ga.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
				//tv = (TextView) findViewById(R.id.textView1);
				tv.setText(nome.get(arg2));
				//Bitmap bm;
				//File imageFile = new File(pics[arg2]);  
		        //if(imageFile.exists())  
		        Bitmap bm = BitmapFactory.decodeFile("/sdcard/fiori/" + pics[arg2]);
		        //else  
		        //	return BitmapFactory.decodeResource(getResources(), R.drawable.imagenotfound);  	         
				imageView.setImageBitmap(bm);
			}
        });
        
        setDefaultImage();
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

    void update(boolean forceUpdate) {
    	File f = new File("/data/data/com.ms.myflowers/databases/fiori.db");
    	if (f.isFile() && !forceUpdate) {
    		dbH  = new dbHandler(this);
            database = dbH.getReadableDatabase();
            readDataBase();
    		return;
    	}

    	if (!isNetworkAvailable(this)) {
			Toast toast = Toast.makeText(this, "Connessione di rete non disponibile\nImpossibile scaricare aggiornamenti.", Toast.LENGTH_LONG);
			toast.show();	
			return;
    	} else {
    		if (forceUpdate)
    			if(database.isOpen())
    				database.close();
    		getDB();
    		
    		dbH  = new dbHandler(this);
            database = dbH.getReadableDatabase();
            readDataBase();
    		
            final int size = checkDirSize();
            
    		openDB = new Runnable(){
    			public void run() {
    				getFiori(size);
    			}
    		};
	        
    		Thread thread =  new Thread(null, openDB, "");
    		thread.start();
    		m_ProgressDialog = new ProgressDialog(this);
    		m_ProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
    		m_ProgressDialog.setMessage("Loading pictures...");
    		m_ProgressDialog.setCancelable(false);
    		m_ProgressDialog.show();
    	}
    }
    
    private int checkDirSize() {
    	int max = 0;
    	files = new String[pics.length + 1];
    	for (int i=0; i<pics.length; i++)
    		files[i] = pics[i];
    	files[pics.length] = "null.jpg";
    	
    	try {
    		URL url = new URL("http://sani.web.cern.ch/sani/fiori/size.txt");
    		URLConnection ucon = url.openConnection();
    		BufferedReader in = new BufferedReader(new InputStreamReader(ucon.getInputStream()));
    		String inputLine;
    		String tot = "";
    		while ((inputLine = in.readLine()) != null) {
    			tot = tot + inputLine;
    		}
    		in.close();
    		max = Integer.parseInt(tot);

    	} catch (MalformedURLException e) {
    		Log.v("DB1", e.getMessage());
    	} catch (IOException e) {
    		Log.v("DB2", e.getMessage());
    	}
		
    	return max;
    }
    
    private void getFiori(final int realTarget) {
    	File f = new File("/sdcard/fiori");
    	if (!f.isDirectory()) {
    		f.mkdir();
    	}
    	
    	try {
    		m_ProgressDialog.setMax(realTarget);
    		
    		int totWritten = 0;
    		for (int i=0; i<files.length; i++) {
    			URL url = new URL("http://sani.web.cern.ch/sani/fiori/"+files[i]);	
    			URLConnection urlconn = url.openConnection();
    			int currentMax = urlconn.getContentLength();
    			InputStream is = urlconn.getInputStream();
    			OutputStream os = new FileOutputStream("/sdcard/fiori/"+files[i]);
    			byte[] buffer = new byte[1024 * 1000];
    			int written = 0;
    			int length = 0;
    			while (written < currentMax) {
    				length = is.read(buffer);
    				os.write(buffer, 0, length);
    				written += length;
    				totWritten += length;
    				final int prog = totWritten;
    				m_ProgressDialog.setProgress(prog);
    			}
	    
    			os.flush();
    			os.close();
    			is.close();
    		}
    	} catch (Exception e) {
    		Log.e("DB", "bad things", e);
    	}
    	runOnUiThread(returnRes);
    } 
    
    private void getDB() {
    	try {
    		Toast toast = Toast.makeText(this, "Downloading DB...", Toast.LENGTH_LONG);
			toast.show();	
			
    		URL url = new URL("http://sani.web.cern.ch/sani/fiori/fiori.db.txt");
    	    URLConnection urlconn = url.openConnection();
    	    final int max = urlconn.getContentLength();    
    	    InputStream is = urlconn.getInputStream();
    	    
    	    File f = new File("/data/data/com.ms.myflowers/databases");
        	if (!f.isDirectory()) {
        		f.mkdir();
        	}
        	
    	    OutputStream os = new FileOutputStream("/data/data/com.ms.myflowers/databases/fiori.db");
    	    
    	    byte[] buffer = new byte[1024 * 1000];
    	    int written = 0;
    	    int length = 0;
    	    while (written < max) {
    	    	length = is.read(buffer);
    	    	os.write(buffer, 0, length);
    	    	written += length;
    	    	//final int prog = written;
    	    }
    	    os.flush();
    	    os.close();
    	    is.close();
    	} catch (Exception e) {
    		Log.e("DB", "bad things", e);
    	}
    }
    		
	private Runnable returnRes = new Runnable() {
        public void run() {
        	m_ProgressDialog.dismiss();
        }
    };
    
    void setDefaultImage() {
    	Bitmap bm = BitmapFactory.decodeFile("/sdcard/fiori/" + pics[0]);
    	tv.setText(nome.get(0));
    	imageView.setImageBitmap(bm);
    	ga.setSelection(0);
    }
    
    public void onCheckboxClicked(View v) {
    	int id = v.getId();
        int f = 0;
    	switch (id) {
    		case R.id.rad_bianco:
    			f = 0;
    			break;
    		case R.id.rad_giallo:
    			f = 1;
    			break;
    		case R.id.rad_arancio:
    			f = 2;
    			break;
    		case R.id.rad_rosso:
    			f = 3;
    			break;
    		case R.id.rad_viola:
    			f = 4;
    			break;
    		case R.id.rad_verde:
    			f = 5;
    			break;
    	}
    	
        if (((CheckBox) v).isChecked())
        	binaryChoice += (int)Math.pow(2, f);
        else 
        	binaryChoice -= (int)Math.pow(2, f);
        
        readDataBase();
        ImageAdapter ar = ((ImageAdapter)ga.getAdapter());
        ar.notifyDataSetChanged();
        setDefaultImage();
    }
    
    private void readDataBase() {
    	nome.clear();
    	file.clear();
    	
    	String q = "select * from fiori where " + Integer.toString(binaryChoice) +"&code order by nome;";
    	Cursor c = database.rawQuery(q,  null);
    	c.moveToFirst();
    	while (c.isAfterLast() == false) {
    		nome.add(c.getString(2));
    		file.add(Integer.toString(c.getInt(3)));
    		c.moveToNext();
    	}
    	c.close();

    	if (nome.size() == 0) {
    		nome.add("---------");
    		pics = new String[1];
    		pics[0] = "null.jpg";
    	} else {
    		pics = new String[nome.size()];
    		for (int i=0; i<nome.size(); i++)
    			pics[i] = "pic_"+ file.get(i) + ".jpg";
    	}
    }
    
    public class ImageAdapter extends BaseAdapter {

    	private Context ctx;
    	int imageBackground;
    	
    	public ImageAdapter(Context c) {
			ctx = c;
			TypedArray ta = ((Activity)c).obtainStyledAttributes(R.styleable.Gallery1);
			imageBackground = ta.getResourceId(R.styleable.Gallery1_android_galleryItemBackground, 1);
			ta.recycle();
		}

		@Override
    	public int getCount() {  		
    		return pics.length;
    	}

    	@Override
    	public Object getItem(int arg0) {  		
    		return arg0;
    	}

    	@Override
    	public long getItemId(int arg0) {  		
    		return arg0;
    	}

    	@Override
    	public View getView(int arg0, View arg1, ViewGroup arg2) {
    		ImageView iv = new ImageView(ctx);
    		iv.setImageBitmap(BitmapFactory.decodeFile("/sdcard/fiori/" + pics[arg0]));
    		iv.setLayoutParams(new Gallery.LayoutParams(120,120));
    		iv.setBackgroundResource(imageBackground);
    		return iv;
    	}

    }   
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.update:     
            	update(true);
            	break;
            case R.id.quit:     
            	finish();
            	break;
        }
        return true;
    }
    
    @Override
    protected void onResume() {
        database = dbH.getReadableDatabase();
        super.onResume();
    }

    @Override
    protected void onPause() {
        database.close();
        super.onPause();
    }
    
    private void handleButton() {
    	Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
    	photoPickerIntent.setType("image/*");
    	startActivityForResult(photoPickerIntent, SELECT_PHOTO);    
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent imageReturnedIntent) { 
        super.onActivityResult(requestCode, resultCode, imageReturnedIntent); 

        switch(requestCode) { 
        case SELECT_PHOTO:
            if(resultCode == RESULT_OK){  
            	try {
            		Uri selectedImage = imageReturnedIntent.getData();
            		InputStream imageStream = getContentResolver().openInputStream(selectedImage);
            		Bitmap yourSelectedImage = BitmapFactory.decodeStream(imageStream);
            		ExifInterface exif = new ExifInterface(selectedImage.getPath());
            		Log.e("LATITUDE EXTRACTED", exif.getAttribute(ExifInterface.TAG_GPS_LATITUDE));
            		Log.e("LONGITUDE EXTRACTED", exif.getAttribute(ExifInterface.TAG_GPS_LONGITUDE));
            	} catch(Exception e) {
            		e.printStackTrace();
                }
            }
        }
    }
}