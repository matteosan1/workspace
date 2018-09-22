package com.ms.dbpalio.masgalano;

import com.ms.dbpalio.R;

import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;

public class MasDetailView extends Dialog implements View.OnClickListener {
	
	Button okButton;

	public MasDetailView(Context context) {
		super(context);
		/** 'Window.FEATURE_NO_TITLE' - Used to hide the title */
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		/** Design the dialog in main.xml file */
		setContentView(R.layout.masdetailedview);
		okButton = (Button) findViewById(R.id.OkButton);
		okButton.setOnClickListener(this);
	}

	public void SetText(MasgalanoModel f) {
		TextView tv1 = (TextView) findViewById(R.id.mas_contrada);
		String s = f.contrada;
		tv1.setText(s);
		
		TextView tv2 = (TextView) findViewById(R.id.mas_data);
		s = f.data;
		tv2.setText(s);
		
		TextView tv3 = (TextView) findViewById(R.id.mas_organizz);
		s = f.organizzatore;
		tv3.setText(s);
		
		TextView tv4 = (TextView) findViewById(R.id.mas_scultore);
		s = f.scultore;
		tv4.setText(s);
		
		TextView tv5 = (TextView) findViewById(R.id.mas_dedica);
		s = f.dedica;
		tv5.setText(s);
		
		TextView tv6 = (TextView) findViewById(R.id.mas_punteggio);
		s = f.punteggio;
		tv6.setText(s);
		
		TextView tv7 = (TextView) findViewById(R.id.mas_note);
		s = f.note;
		tv7.setText(s);
		
	}
		
	public void onClick(View v) {
		/** When OK Button is clicked, dismiss the dialog */
		if (v == okButton)
			dismiss();
	}
}