package edu.calpoly.android.apprater;


import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.Cursor;
import android.location.GpsStatus.Listener;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import edu.calpoly.android.appraterkey.AppContentProvider;
import edu.calpoly.android.appraterkey.AppDownloadService;

public class AppRater extends Activity implements OnItemClickListener{

	/** MenuItem Constants to be used for the Options Menu **/
	private static final int MENU_ITEM_STARTDOWNLOAD = Menu.FIRST;
	private static final int MENU_ITEM_STOPDOWNLOAD = Menu.FIRST + 1;
	private static final int MENU_ITEM_REMOVEALL = Menu.FIRST+2;

	/** MenuItem Constants to be used for the Context Menu **/
	private static final int MENU_ITEM_INSTALLED = Menu.FIRST;
	private static final int MENU_ITEM_RATING1 = Menu.FIRST + 1;
	private static final int MENU_ITEM_RATING2 = Menu.FIRST + 2;
	private static final int MENU_ITEM_RATING3 = Menu.FIRST + 3;
	private static final int MENU_ITEM_RATING4 = Menu.FIRST + 4;
	private static final int MENU_RATING_GROUP = Menu.FIRST;

	/** The ListView that contains the List of AppViews. **/
	private ListView m_vwAppList;

	/** The Cursor that contains the Apps. **/
	private Cursor m_cursorApps;

	/** The CursorAdapter used to bind the Cursor to AppViews. **/
	private AppCursorAdapter m_cursorAdapter;

	/**
	 * The BroadcastReceiver used to listen for new Apps that have been added by
	 * the AppDownloadService.
	 */
	private AppReceiver m_receiver;

	private static final String ORDER_BY_STRING = AppContentProvider.APP_KEY_INSTALLED + ", " +
												  AppContentProvider.APP_KEY_RATING + ", " +
												  AppContentProvider.APP_KEY_NAME;
	
	private static final int NOTIFICATION_ID = AppDownloadService.NEW_APP_NOTIFICATION_ID;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.app_list);
//		2.1.1 Fill in onCreate(...)
		// Init Cursor & Adapter
		// TODO
		m_cursorApps = managedQuery(AppContentProvider.CONTENT_URI,
				null,null,null,null);
//		startManagingCursor(m_cursorApps);//manage an unmanaged cursor
		m_cursorAdapter = new AppCursorAdapter(this,m_cursorApps);
		
		// Init View Components
		// TODO
		m_vwAppList = (ListView)findViewById(R.id.m_vwAppList);
		m_vwAppList.setAdapter(m_cursorAdapter);
		m_vwAppList.setOnItemClickListener(this);
		registerForContextMenu(m_vwAppList);	
	}
	
	@Override
	public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
		// TODO Auto-generated method stub
		App myApp = ((AppView) view).getApp();
		Uri uri = Uri.parse(myApp.getInstallURI());
		Intent intent = new Intent(Intent.ACTION_VIEW,uri);
//		try {     
			startActivity(intent); 
//		}  
//		catch (ActivityNotFoundException e) {     //?????/??????????????
//			Toast.makeText(getApplicationContext(),
//					"Unable to get App from Market",
//					Toast.LENGTH_SHORT)
//					.show();
//		}
	}
	

//	2.2.1 Create the Options Menu
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		menu.add(0,AppRater.MENU_ITEM_STARTDOWNLOAD,Menu.NONE,"Start Downloading");
		menu.add(0,AppRater.MENU_ITEM_STOPDOWNLOAD,Menu.NONE, "Stop Downloading");
		menu.add(0,AppRater.MENU_ITEM_REMOVEALL,Menu.NONE, "Remove All Apps");
		return true;}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int itemId = item.getItemId();
		Log.i("lab6","1");
		switch (itemId) {
		case AppRater.MENU_ITEM_STARTDOWNLOAD: 
			 Intent intent1 = new Intent(AppRater.this,AppDownloadService.class);
			 startService(intent1);
			 Log.i("lab6","2");
			 return false;//??????????????????????????????????????
		case AppRater.MENU_ITEM_STOPDOWNLOAD:
			 Intent intent2 = new Intent(AppRater.this,AppDownloadService.class);
			 stopService(intent2);
			 return true;
		case AppRater.MENU_ITEM_REMOVEALL: 
			 getContentResolver().delete(AppContentProvider.CONTENT_URI, null, null);
			 return true;
		default :
			return super.onOptionsItemSelected(item);
		}
	}

	/**
	 * Inner class that defines a BroadcastReciever which listens for Intents
	 * broadcasted by the AppDownloadService when it has downloaded a new App.
	 */
	public class AppReceiver extends BroadcastReceiver {

		/**
		 * This method gets called when the AppDownloadService broadcasts
		 * intents
		 */

//		2.3.1 Implement the AppRater.AppReceiver Class
		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO
			if(intent.getAction().equals(AppDownloadService.NEW_APP_TO_REVIEW)){
				Log.i("lab6", "receive");
				Toast.makeText(context,
						getResources().getString(R.string.newAppToast),
						Toast.LENGTH_SHORT)
						.show();
			}
			else return;
		}
	}
	
//	2.3.1 Register & Un-Register for Broadcasts
	@Override
	protected void onResume(){
		m_receiver = new AppReceiver();
		IntentFilter intentFilter = new IntentFilter(
										AppDownloadService.NEW_APP_TO_REVIEW);
		registerReceiver(m_receiver, intentFilter);
		
	}
	
	@Override
	protected void onPause(){
		unregisterReceiver(m_receiver);
	}
}