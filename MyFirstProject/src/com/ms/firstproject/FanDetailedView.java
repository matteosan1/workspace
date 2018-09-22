package com.ms.firstproject;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

/** Class Must extends with Dialog */
/** Implement onClickListener to dismiss dialog when OK Button is pressed */
public class FanDetailedView extends Dialog implements OnClickListener {
	Button okButton;

	public FanDetailedView(Context context) {
		super(context);
		/** 'Window.FEATURE_NO_TITLE' - Used to hide the title */
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		/** Design the dialog in main.xml file */
		setContentView(R.layout.fandetailedview);
		okButton = (Button) findViewById(R.id.OkButton);
		okButton.setOnClickListener(this);
	}

	public void SetText(FantinoModel f) {
		TextView tv = (TextView) findViewById(R.id.TextView02);
		String s = f.getNome() + " detto " + f.getFantino() + "\n";
		s = s + "Nato a " + f.getCitta() + " il " + f.getNascita() + "\n\nCarriere\n";
		tv.setText(s);
		
		ListView list = (ListView) findViewById(R.id.listcarriere);
		 
		ArrayList<HashMap<String, String>> mylist = new ArrayList<HashMap<String, String>>();
		HashMap<String, String> map = new HashMap<String, String>();
		
		for (int i=0; i<f.getDate().size(); i++) {	
			map = new HashMap<String, String>();
			map.put("anno", f.getDate().get(i));
			map.put("contrada", f.getContrade().get(i));
			map.put("cavallo", f.getCavalli().get(i));
			mylist.add(map);
		}
		
		SimpleAdapter mSchedule = new SimpleAdapter(this.getContext(), mylist, R.layout.row,
		            new String[] {"anno", "contrada", "cavallo"}, new int[] {R.id.anno, R.id.contrada, R.id.cavallo});
		list.setAdapter(mSchedule);
	}
		
	public void onClick(View v) {
		/** When OK Button is clicked, dismiss the dialog */
		if (v == okButton)
			dismiss();
	}
}