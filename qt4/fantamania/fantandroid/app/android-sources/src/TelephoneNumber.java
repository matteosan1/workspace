package com.example.android.tools;

import android.util.Log;
import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import org.qtproject.qt5.android.QtNative;

public class TelephoneNumber  {
    public static String phoneNumber() {
	String msgTag = "PNumber";
	try {
	    Log.v(msgTag, "start phoneNumber");
	    if (QtNative.activity() == null)
		return "";
	    
	    //TelephonyManager telephonyManager;
	    //telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
	    return "0041762348897";//telephonyManager.getDeviceId();
	}
	catch (Exception e) {
	    Log.e(msgTag, e.toString());
	    e.printStackTrace();
	    return "";
	}
    }
}
