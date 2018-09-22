package com.ms.bluetooth;

import java.util.ArrayList;
import java.util.Set;

import android.app.ListActivity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class BluetoothActivity extends ListActivity {
	
	final int REQUEST_ENABLE_BT = 10;
	BluetoothAdapter mBluetoothAdapter;
	ListView lv;
	Button discovery;
	ArrayList<String> listaNomi = new ArrayList<String>();
	TextView tv;
	ButtonHandler buttonHandler = new ButtonHandler();
	
	private class ButtonHandler implements View.OnClickListener {
		ArrayAdapter<String> adapter;
		void setButtonHandler(final ArrayAdapter<String> a) {
			adapter = a;
		}
        public void onClick(View v)     {
        	if (v.getId() == R.id.button1)
        		handleButton(adapter);
        }       
    }
        
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        lv = (ListView) findViewById(android.R.id.list);
        lv.setOnItemClickListener(connectWithDevice);

        tv = (TextView) findViewById(R.id.text);

        discovery = (Button) findViewById(R.id.button1);
        discovery.setOnClickListener(buttonHandler);  

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
        	Log.v("test", "OHOHOHOHOHOHOHO");
            // Device does not support Bluetooth
        }
        
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }
    
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
    	if (resultCode == RESULT_OK) {
    		listaNomi.clear();
    		Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
    		if (pairedDevices.size() > 0) {
    		    for (BluetoothDevice device : pairedDevices) {
    		    	listaNomi.add(device.getName() + " - " + device.getAddress());
    		    }
    		}
    		ArrayAdapter<String> mioAdapter = new ArrayAdapter<String>
    				(this, android.R.layout.simple_list_item_1, listaNomi);
    		this.setListAdapter(mioAdapter);
    		buttonHandler.setButtonHandler(mioAdapter);
    		
    		Log.v("test", "OK");
    	} else {
    		Log.v("test", "NO");
    	}
    }
    
    private OnItemClickListener connectWithDevice = new OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, 
                    View view, int position, long id) {
        	tv.setText(listaNomi.get(position));
        }
    };

    private void handleButton(final ArrayAdapter<String> ada) {
 
    	// Create a BroadcastReceiver for ACTION_FOUND
    	final BroadcastReceiver mReceiver = new BroadcastReceiver() {
    		public void onReceive(Context context, Intent intent) {
    			String action = intent.getAction();
    	        	// When discovery finds a device
    	        if (BluetoothDevice.ACTION_FOUND.equals(action)) {
    	            // Get the BluetoothDevice object from the Intent
    	        	BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
    	            // Add the name and address to an array adapter to show in a ListView
    	        	listaNomi.add(device.getName() + " - " + device.getAddress());
    	        	buttonHandler.adapter.notifyDataSetChanged();
    	        }
    	    }
    	};
    	
    	 // Register the BroadcastReceiver
    	IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
    	registerReceiver(mReceiver, filter); // Don't forget to unregister during onDestroy
    	//All that's needed from the BluetoothDevice object in order to initiate a connection is the MAC address. In this example, it's saved as a part of an ArrayAdapter that's shown to the user. The MAC address can later be extracted in order to initiate the connection. You can learn more about creating a connection in the section about Connecting Devices.

    	//Caution: Performing device discovery is a heavy procedure for the Bluetooth adapter and will consume a lot of its resources. Once you have found a device to connect, be certain that you always stop discovery with cancelDiscovery() before attem
    }

}





/*
 * Intent discoverableIntent = new
Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
startActivity(discoverableIntent);
*/


/*
 * private class AcceptThread extends Thread {
    private final BluetoothServerSocket mmServerSocket;
 
    public AcceptThread() {
        // Use a temporary object that is later assigned to mmServerSocket,
        // because mmServerSocket is final
        BluetoothServerSocket tmp = null;
        try {
            // MY_UUID is the app's UUID string, also used by the client code
            tmp = mBluetoothAdapter.listenUsingRfcommWithServiceRecord(NAME, MY_UUID);
        } catch (IOException e) { }
        mmServerSocket = tmp;
    }
 
    public void run() {
        BluetoothSocket socket = null;
        // Keep listening until exception occurs or a socket is returned
        while (true) {
            try {
                socket = mmServerSocket.accept();
            } catch (IOException e) {
                break;
            }
            // If a connection was accepted
            if (socket != null) {
                // Do work to manage the connection (in a separate thread)
                manageConnectedSocket(socket);
                mmServerSocket.close();
                break;
            }
        }
    }
 
    public void cancel() {
        try {
            mmServerSocket.close();
        } catch (IOException e) { }
    }
}

*/

/*
 * private class ConnectedThread extends Thread {
    private final BluetoothSocket mmSocket;
    private final InputStream mmInStream;
    private final OutputStream mmOutStream;
 
    public ConnectedThread(BluetoothSocket socket) {
        mmSocket = socket;
        InputStream tmpIn = null;
        OutputStream tmpOut = null;
 
        // Get the input and output streams, using temp objects because
        // member streams are final
        try {
            tmpIn = socket.getInputStream();
            tmpOut = socket.getOutputStream();
        } catch (IOException e) { }
 
        mmInStream = tmpIn;
        mmOutStream = tmpOut;
    }
 
    public void run() {
        byte[] buffer = new byte[1024];  // buffer store for the stream
        int bytes; // bytes returned from read()
 
        // Keep listening to the InputStream until an exception occurs
        while (true) {
            try {
                // Read from the InputStream
                bytes = mmInStream.read(buffer);
                // Send the obtained bytes to the UI activity
                mHandler.obtainMessage(MESSAGE_READ, bytes, -1, buffer)
                        .sendToTarget();
            } catch (IOException e) {
                break;
            }
        }
    }
 
    public void write(byte[] bytes) {
        try {
            mmOutStream.write(bytes);
        } catch (IOException e) { }
    }
 
    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) { }
    }
}
*/
