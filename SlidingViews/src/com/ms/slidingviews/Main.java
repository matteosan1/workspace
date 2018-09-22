package com.ms.slidingviews;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class Main extends Activity {

   /** Called when the activity is first created. */
   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.main);

      Button onebutton = (Button)findViewById(R.id.soundsone);
      onebutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series1button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);
         }
      });

      Button twobutton = (Button)findViewById(R.id.soundstwo);
      twobutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series2button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);
         }
      });

      Button threebutton = (Button)findViewById(R.id.soundsthree);
      threebutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series3button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);           
         }
      });

      Button fourbutton = (Button)findViewById(R.id.soundsfour);
      fourbutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series4button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);
         }
      });

      Button fivebutton = (Button)findViewById(R.id.soundsfive);
      fivebutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series5button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);
         }
      });

      Button sixbutton = (Button)findViewById(R.id.soundssix);
      sixbutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series6button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);
         }
      });

      Button sevenbutton = (Button)findViewById(R.id.soundsseven);
      sevenbutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series7button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);           
         }
      });

      Button eightbutton = (Button)findViewById(R.id.soundseight);
      eightbutton.setOnClickListener(new OnClickListener() {
         public void onClick(View v) {
            Intent i = new Intent(main.this, series8button.class);
            startActivity(i);
            overridePendingTransition(R.anim.push_up_in, R.anim.push_up_out);           
         }
      });
   }
}