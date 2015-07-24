package szhao.bluetooth;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.Toast;
import android.widget.AdapterView.AdapterContextMenuInfo;

public class BluetoothReminder extends Activity {
	/** Called when the activity is first created. */

	private Button appSetting;
	private LinearLayout linearLayout01;
	private boolean isSound;
	private int time;
	private int id;
	private boolean remindState;
	private Device myDevice;
//	private View currentView;
	BluetoothSocket mySocket = null;
	private BluetoothAdapter blueAdapter = null;
	// private RemindService mRemindService = null;
//	 private stateReceiver m_receiver;

	private static final UUID MY_UUID = UUID
			.fromString("5f21ed36-0d49-4061-8312-984f98db7521");

	private static final int START_SETTING = 1;
	private static final int REQUEST_ENABLE_BT = 3;

	protected static final String SAVED_SOUND_VALUE = "isSound";
	protected static final String SAVED_TIME_VALUE = "time";
	protected static final String SAVED_IMAGE_VALUE = "image";
	protected static final String REMOTE_DEVICE_NAME = "remoteDeviceName";
	protected static final String STOP = "stop";

	/** MenuItem Constants to be used for the Context Menu **/
	private static final int MENU_ITEM_REMIND = Menu.FIRST + 1;
	private static final int MENU_ITEM_IGNORE = Menu.FIRST + 2;
	private static final int MENU_GROUP = Menu.FIRST;
	/**
	 * Contains the list of Devices the Activity will present to the user.
	 **/
	protected ArrayList<Device> deviceList;
	/**
	 * Adapter used to bind an AdapterView to List of Devices.
	 */
	protected DeviceAdapter deviceAdapter;
	/**
	 * ViewGroup used for maintaining a list of Views that each display devices.
	 **/
	protected ListView deviceLayout;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		// Get saved preference
		isSound = PreferenceManager.getDefaultSharedPreferences(this)
				.getBoolean(SAVED_SOUND_VALUE, true);
		time = PreferenceManager.getDefaultSharedPreferences(this).getInt(
				SAVED_TIME_VALUE, 1);
		id = PreferenceManager.getDefaultSharedPreferences(this).getInt(
				SAVED_IMAGE_VALUE, 2130837504);
		// Log.i("test","in main:"+id);
		// Log.i("test","in main:02:"+R.drawable.background02);
		// Log.i("test","in main:03:"+R.drawable.background03);

		// initialLayout
		linearLayout01 = (LinearLayout) findViewById(R.id.linearLayout01);
		linearLayout01.setBackgroundResource(R.drawable.background01);
		Log.i("test", "01:" + R.drawable.background01);

		appSetting = (Button) findViewById(R.id.appSetting);
		appSetting.setOnClickListener(settingListener);

		Log.i("test", "time initial:" + time);
		// isSound = m_bool;
		// time = m_int;
		remindState = false;

		// enable bluetooth
		blueAdapter = BluetoothAdapter.getDefaultAdapter();
		// If the adapter is null, then Bluetooth is not supported
		if (blueAdapter == null) {
			Toast.makeText(this, "Bluetooth is not available",
					Toast.LENGTH_LONG).show();
			finish();
			return;
		}

		deviceAdapter = new DeviceAdapter(this, deviceList);
		deviceLayout = (ListView) findViewById(R.id.deviceList);
		deviceLayout.setAdapter(deviceAdapter);
		Set<BluetoothDevice> bondDevice = blueAdapter.getBondedDevices();
		ArrayList<BluetoothDevice> arraylist = new ArrayList<BluetoothDevice>(bondDevice);
		for (int ndx = 0; ndx < arraylist.size(); ndx++) {
			Device device = new Device(arraylist.get(ndx));
			deviceList.add(device);
			deviceAdapter.notifyDataSetChanged();
		}

		if (!blueAdapter.isEnabled()) {
			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
		} else
			registerForContextMenu(deviceLayout);

		linearLayout01 = (LinearLayout) findViewById(R.id.linearLayout01);
		linearLayout01.setBackgroundResource(id);
		
		 IntentFilter intentFilter1 = new IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED);
		 registerReceiver(m_receiver, intentFilter1);
	}

	// setting listener
	private Button.OnClickListener settingListener = new Button.OnClickListener() {
		@Override
		public void onClick(View v) {
			// linearLayout01 = (LinearLayout)findViewById(R.id.linearLayout01);
			// linearLayout01.setBackgroundResource(R.drawable.background01);
			// Switch to setting page
			Intent intent = new Intent(BluetoothReminder.this, AppSetting.class);
			intent.putExtra(SAVED_SOUND_VALUE, isSound);
			intent.putExtra(SAVED_TIME_VALUE, time);
			intent.putExtra(SAVED_IMAGE_VALUE, id);
			Log.i("test", "pass id:" + id);
			startActivityForResult(intent, START_SETTING);
		}
	};

	public final BroadcastReceiver m_receiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (BluetoothDevice.ACTION_ACL_CONNECTED.equals(action)){
				BluetoothDevice currentDevice = 
					intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				myDevice = (Device) deviceAdapter.getItem(currentDevice.getName());
				if(myDevice == null);
				else{
					((Device) deviceAdapter.getItem(currentDevice.getName())).setConnection(true);
					deviceAdapter.notifyDataSetChanged();
				}
			}
		}
	};
	@Override
	public void onCreateContextMenu(ContextMenu menu, View view,
			ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, view, menuInfo);

		AdapterContextMenuInfo temp = (AdapterContextMenuInfo) menuInfo;
		final DeviceView m_view = (DeviceView) temp.targetView;
		final Device device = m_view.getDevice();

		MenuItem item1 = menu.add(MENU_GROUP, MENU_ITEM_REMIND, Menu.NONE,
				"Remind");
		MenuItem item2 = menu.add(MENU_GROUP, MENU_ITEM_IGNORE, Menu.NONE,
				"Ignore");
		menu.setGroupCheckable(MENU_GROUP, true, true);

	    if(!device.isConnection()){
	    	item1.setEnabled(false);
	    	item2.setEnabled(false);
	    }
	    else{
	    	if(device.isRemind()){
	    		item1.setChecked(true);
	    		item2.setEnabled(true);
	    	}
	    	else{
	    		item1.setEnabled(true);
	    		item2.setEnabled(true);
	    		}		
	    }

		item1.setOnMenuItemClickListener(new OnMenuItemClickListener() {

			@Override
			public boolean onMenuItemClick(MenuItem item) {
				// TODO Auto-generated method stub
//				myDevice = device;
//				remindState = true;
				device.setOperation(true);
				deviceAdapter.notifyDataSetChanged();
				// m_view.setBackgroundColor(R.color.remind);
				Intent intent1 = new Intent(BluetoothReminder.this,
						RemindService.class);
				intent1.putExtra("m_time", time);
				// Log.i("test","mtime in activity"+time);
				bindService(intent1, mConnection, Context.BIND_AUTO_CREATE);
				// handler.handleMessage(msg);
				// BluetoothSocket.getRemoteDevice();
//				currentView = m_view;
				return true;
			}

		});
		item2.setOnMenuItemClickListener(new OnMenuItemClickListener() {

			@Override
			public boolean onMenuItemClick(MenuItem item) {
				// TODO Auto-generated method stub
				Intent intent2 = new Intent(BluetoothReminder.STOP);
				sendBroadcast(intent2);
//				myDevice = null;
//				reminderState = false;
//				deviceLayout.setBackgroundColor(Color.alpha(0));
//				Intent intent2 = new Intent(BluetoothReminder.STOP);
//				sendBroadcast(intent2);
				device.setOperation(false);
				return true;
			}

		});
	}// end onCreateContextMenu

	private Handler handler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case RemindService.CONNECTED:
//				Log.i("test","got in?");
				connectWrong(((BluetoothDevice) msg.obj).getName());
				break;
			case RemindService.UNCONNECTED:
				Log.i("test","got in?");
				((Device) deviceAdapter.getItem(myDevice.getName())).setConnection(false);
				deviceAdapter.notifyDataSetChanged();
				disconnected();
				break;
			default:
				super.handleMessage(msg);
			}
		}
	};

	private ServiceConnection mConnection = new ServiceConnection() {
		// private DownloadService mService;

		private RemindService mRemindService;

		@Override
		public void onServiceConnected(ComponentName className, IBinder binder) {

			// LocalService instance
			mRemindService = ((RemindService.MyBinder) binder).getService();
			Log.i("test",
					"test mRemindService:" + mRemindService.getPackageName());
			// sets the handler here
			mRemindService.setHandler(handler);

		}

		@Override
		public void onServiceDisconnected(ComponentName arg0) {
			mRemindService.setHandler(null);
		}
	};

	/**
	 * Inner class that defines a BroadcastReciever which listens for Intents
	 * broadcasted by the RemindService when device is unconnected.
	 */
	// public class stateReceiver extends BroadcastReceiver {
	// /**
	// * This method gets called when the RemindService broadcasts intents
	// */
	// @Override
	// public void onReceive(Context context, Intent intent) {
	// TODO
	// if (intent.getAction().equals(RemindService.CONNECTED)) {
	// String remoteName = intent.getExtras().getString(
	// REMOTE_DEVICE_NAME);
	// Log.i("test", "remotename:" + remoteName);
	// if (myDevice.getName() != remoteName) {
	// currentView.setBackgroundColor(Color.GRAY);
	// reminderState = false;
	// Intent intent3 = new Intent(BluetoothReminder.this,
	// RemindService.class);
	// stopService(intent3);
	// new AlertDialog.Builder(BluetoothReminder.this)
	// .setTitle(" Warnning!")
	// .setMessage(
	// myDevice.getName()
	// + "isn't connected!/n"
	// + remoteName
	// + " is connected!/n"
	// + "Please choose the correct remind device!")
	// .setPositiveButton("OK",
	// new DialogInterface.OnClickListener() {
	// public void onClick(
	// DialogInterface dialoginterface,
	// int i) {
	// }
	// })
	//
	// .show();
	// myDevice = null;
	// } else
	// return;
	// }
	// if (intent.getAction().equals(RemindService.UNCONNECTED)) {

	// int viewId=deviceLayout.getCheckedItemPosition();
	// View currentView = deviceLayout.getSelectedView();
	// currentView.setBackgroundColor(Color.RED);
	//
	// final MediaPlayer mp = MediaPlayer.create(
	// BluetoothReminder.this, R.raw.msg);
	// if (isSound == true)
	// mp.start();
	// // Switch to setting page
	// new AlertDialog.Builder(BluetoothReminder.this)
	// .setTitle(" Reminding ")
	// .setMessage("Don't forget your Bluetooth Device!")
	// .setPositiveButton("OK",
	// new DialogInterface.OnClickListener() {
	// public void onClick(
	// DialogInterface dialoginterface,
	// int i) {
	// if (isSound == true)
	// mp.stop();
	// }
	// })
	//
	// .show();
	// } else
	// return;
	// }
	// }

	// protected void onResume() {
	// super.onResume();
	// m_receiver = new stateReceiver();
	// IntentFilter intentFilter1 = new IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED);
	// registerReceiver(m_receiver, intentFilter1);
	// IntentFilter intentFilter2 = new IntentFilter(RemindService.CONNECTED);
	// registerReceiver(m_receiver, intentFilter2);
	//
	// }
	//
	// @Override
	// protected void onPause() {
	// super.onPause();
	// unregisterReceiver(m_receiver);
	// }

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == START_SETTING) {
			if (resultCode == Activity.RESULT_CANCELED) {
				return;
			}
			if (resultCode == Activity.RESULT_OK) {
				isSound = data.getExtras().getBoolean(
						AppSetting.CHECKED_SOUND_VALUE);
				time = data.getExtras().getInt(AppSetting.CHECKED_TIME_VALUE);
				id = data.getExtras().getInt(SAVED_IMAGE_VALUE);
//				Log.i("test", "id:" + id);
				linearLayout01 = (LinearLayout) findViewById(R.id.linearLayout01);
				linearLayout01.setBackgroundResource(id);
				Log.i("lab6", "checkedtime:" + time);
				SharedPreferences.Editor mySPEditor = PreferenceManager
						.getDefaultSharedPreferences(this).edit();
				mySPEditor.putBoolean(SAVED_SOUND_VALUE, isSound);
				mySPEditor.putInt(SAVED_TIME_VALUE, time);
				mySPEditor.putInt(SAVED_IMAGE_VALUE, id);
				mySPEditor.commit();
			}
		} else if (requestCode == REQUEST_ENABLE_BT) {
			// When the request to enable Bluetooth returns
			if (resultCode == Activity.RESULT_OK) {
				// Bluetooth is now enabled, so set up a chat session
				registerForContextMenu(deviceLayout);
			} else {
				// User did not enable Bluetooth or an error occurred
				Toast.makeText(this, "Bluetooth cannot setup",
						Toast.LENGTH_SHORT).show();
				try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				finish();
			}
		} else
			return;
	}

	public void connectWrong(String name) {
//		Log.i("test","name:"+name);
		if (!myDevice.getName().equals(name)) {
//			Log.i("test","myDevice name:"+myDevice.getName());
//			reminderState = false;
			Intent intent3 = new Intent(BluetoothReminder.this,
					RemindService.class);
			stopService(intent3);
			new AlertDialog.Builder(BluetoothReminder.this)
					.setTitle(" Warnning!")
					.setMessage(
							myDevice.getName()
									+ "isn't connected!\n"
									+ name
									+ " is connected!\n"
									+ "Please choose the correct remind device!")
					.setPositiveButton("OK",
							new DialogInterface.OnClickListener() {
								public void onClick(
										DialogInterface dialoginterface, int i) {
								}
							})

					.show();
			myDevice = null;
		}
//		else currentView.setBackgroundColor(Color.YELLOW);
	}

	public void disconnected() {
//		currentView.setBackgroundColor(Color.RED);
		final MediaPlayer mp = MediaPlayer.create(BluetoothReminder.this,
				R.raw.msg);
		if (isSound == true)
			mp.start();
		// Switch to setting page
		new AlertDialog.Builder(BluetoothReminder.this).setTitle(" Reminding ")
				.setMessage("Don't forget your Bluetooth Device!")
				.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialoginterface, int i) {
						if (isSound == true)
							mp.stop();
					}
				})

				.show();

	}
}