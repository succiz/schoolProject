package szhao.bluetooth;

import java.util.Timer;
import java.util.TimerTask;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class RemindService extends Service {
	/**
	 * The Timer thread which will execute the check for connection. Acts like a
	 * Thread that can be told to start at a specific time and/or at specific
	 * time intervals.
	 */
	private Timer m_updateTimer;

	// /**
	// * The TimerTask which encapsulates the logic that will check for
	// * connection. This ends up getting run by the Timer in the same way that
	// a
	// * Thread runs a Runnable.
	// */
	// private TimerTask m_updateTask;

	/**
	 * The time frequency at which the service should check the server for new
	 * Connection.
	 */
	private long updateFrequency;
	private boolean isConnected;
	private int count;
	private Handler myHandler;
	private Message message;
	/**
	 * The Action String for the Intent that this service broadcasts when a
	 * device has been unconnected.
	 */
	public static final int UNCONNECTED = 0;
	public static final int CONNECTED = 1;

	/** Initialize your member variables here **/
	@Override
	public void onCreate() {
		// TODO
		IntentFilter filter1 = new IntentFilter(
				BluetoothDevice.ACTION_ACL_DISCONNECTED);
		IntentFilter filter2 = new IntentFilter(
				BluetoothDevice.ACTION_ACL_CONNECTED);
		IntentFilter filter3 = new IntentFilter(
				BluetoothReminder.STOP);
		// this.registerReceiver(mReceiver, filter1);
		this.registerReceiver(mReceiver, filter1);
		this.registerReceiver(mReceiver, filter2);
		this.registerReceiver(mReceiver, filter3);
		isConnected = true;

	}

//	@Override
//	public int onStartCommand(Intent intent, int flags, int startId) {
//
////		updateFrequency = intent.getExtras().getInt("m_time") * 30000;
////		Log.i("test", "service:" + updateFrequency);
////
////		m_updateTimer = new Timer();
////		m_updateTimer.schedule(new TimerTask() {
////			@Override
////			public void run() {
////				// TODO Auto-generated method stub
////				checkState();
////			}
////		}, 0, updateFrequency);
//
//		return startId;
//	}

//	/** Cleanup any and all resources here. All Timer's should be canceled here. **/
//	@Override
//	public void onDestroy() {
//		// TODO
//
//		m_updateTimer.cancel();
//		m_updateTimer = null;
//	}

	/**
	 * check Bluetooth device state if connected return true disconnected return
	 * false, broadcast itself and stop service
	 */
	private void checkState() {
		// IntentFilter filter1 = new
		// IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED);
		if (!isConnected) {
			// Intent intentBroad = new Intent(RemindService.UNCONNECTED);
			// sendBroadcast(intentBroad);
			Log.i("test","isConnected"+isConnected);
			message = Message.obtain(myHandler, UNCONNECTED);
			myHandler.sendMessage(message);
		}
	}

	public final BroadcastReceiver mReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();

//			if (BluetoothDevice.ACTION_ACL_CONNECTED.equals(action)) {
//				// Intent intent1 = new Intent(RemindService.CONNECTED);
//				// intent.putExtra(BluetoothReminder.REMOTE_DEVICE_NAME,
//				// device.getName());
//				// Log.i("test","device name:"+device.getName());
//				// sendBroadcast(intent1);
//				BluetoothDevice device = intent
//				.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
//				message = Message.obtain(myHandler, CONNECTED, device);
//				myHandler.sendMessage(message);
//			}
			if (BluetoothDevice.ACTION_ACL_DISCONNECTED.equals(action)) {
				// Device has disconnected
				isConnected = false;
				Log.i("test","isConnected"+isConnected);
			} else if(BluetoothReminder.STOP.equals(action)){
				m_updateTimer.cancel();
				m_updateTimer = null;
				Log.i("test","timer:"+m_updateTimer);
				stopSelf();
//				m_updateTimer.cancel();
//				m_updateTimer = null;
//				Log.i("test","timer:"+m_updateTimer);
			}
			else return;
		}
	};

	public void setHandler(Handler handler) {
		myHandler = handler;
	}

	private IBinder binder = new MyBinder();

	public class MyBinder extends Binder {
		public RemindService getService() {
			Log.i("test","myBinder:");
			return RemindService.this;
		}
	};

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		// Binder mybinder = new Binder(){
		// public RemindService getService(){
		// return RemindService.this;
		// }
		// };
		updateFrequency = intent.getExtras().getInt("m_time") * 30000;
		Log.i("test", "service:" + updateFrequency);

		m_updateTimer = new Timer();
		m_updateTimer.schedule(new TimerTask() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				checkState();
			}
		}, 0, updateFrequency);
		Log.i("test","m_updateTimer:"+m_updateTimer);
		return binder;
	}
}
