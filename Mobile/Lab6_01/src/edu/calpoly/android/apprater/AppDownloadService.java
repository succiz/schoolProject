package edu.calpoly.android.apprater;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import edu.calpoly.android.appraterkey.AppContentProvider;

public class AppDownloadService extends Service {

	/**
	 * The Timer thread which will execute the check for new Apps. Acts like a
	 * Thread that can be told to start at a specific time and/or at specific
	 * time intervals.
	 */
	private Timer m_updateTimer;

	/**
	 * The TimerTask which encapsulates the logic that will check for new Apps.
	 * This ends up getting run by the Timer in the same way that a Thread runs
	 * a Runnable.
	 */
	private TimerTask m_updateTask;

	/**
	 * The time frequency at which the service should check the server for new
	 * Apps.
	 */
	private static final long UPDATE_FREQUENCY = 10000L;

	/**
	 * The ID for the Notification that is generated when a new App is added
	 */
	public static final int NEW_APP_NOTIFICATION_ID = 1;
	
	/**
	 * The Action String for the Intent that this service broadcasts when a new
	 * App has been downloaded and added successfully.
	 */
	public static final String NEW_APP_TO_REVIEW = "New_App_To_Review";

	/** 
	 * A String containing the URL from which to download the list of all Apps. 
	 */
	public static final String GET_APPS_URL = "http://www.simexusa.com/aac/getAllApps.php";
	
	public static final String DUMMY_STRING = AppContentProvider.APP_KEY_INSTALLURI;

	/** Initialize your member variables here **/
	@Override
	public void onCreate() {
		// TODO
	}

	/** Cleanup any and all resources here. All Timer's should be canceled here. **/
	@Override
	public void onDestroy() {
		// TODO
	}

	/** Ignore this method, you won't be using it. **/
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	/**
	 * This method downloads all of the Apps from the App server. For each App,
	 * it checks the AppContentProvider to see if it has already been downloaded
	 * before. If it is new, then it adds it to the AppContentProvider by
	 * calling addNewApp.
	 */
	private void getAppsFromServer() {
		// TODO
	}

	/**
	 * This method add's a new App to the AppContentProvider.
	 * 
	 * @param app
	 *            The new App object to add to the ContentProvider.
	 */
	private void addNewApp(App app) {
		// TODO
	}

	/**
	 * This method broadcasts an intent with the NEW_APP_TO_REVIEW Action
	 * String. This method should be called when a new App has been downloaded
	 * and added successfully. This method should also create a new Notification
	 */
	private void announceNewApp() {
		// TODO
	}
}
