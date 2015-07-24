package edu.calpoly.android.walkabout;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Settings;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.widget.Toast;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.MyLocationOverlay;
import com.google.android.maps.Overlay;
import com.google.android.maps.OverlayItem;

import edu.calpoly.android.walkabout.R;

public class WalkAbout extends MapActivity implements LocationListener {

	private MapView m_vwMap;
	private MapController m_mapController;
	private PathOverlay m_pathOverlay;
	private MyLocationOverlay m_locationOverlay;
	
	private ArrayList<GeoPoint> m_arrPathPoints;
	private ArrayList<OverlayItem> m_arrPicturePoints;//?
	private LocationManager m_locManager;
	private boolean m_bRecording;

	private static final double GEO_CONVERSION = 1E6;
	private static final int MIN_TIME_CHANGE = 3000;
	private static final int MIN_DISTANCE_CHANGE = 3;
	
	private static final int PICTURE_REQUEST_CODE = 0;
	private static final int ENABLE_GPS_REQUEST_CODE = 1;
	
	private static final int STARTSTOP_MENU_ITEM = Menu.FIRST;
	private static final int SAVE_MENU_ITEM = Menu.FIRST+1;
	private static final int LOAD_MENU_ITEM = Menu.FIRST+2;
	private static final int PICTURE_MENU_ITEM = Menu.FIRST+3;
	private static final int ENABLEGPS_MENU_ITEM = Menu.FIRST+4;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState); 
        initLocationData();
        initLayout(); 
        Log.i("lab5","this is 1");
    }
	@Override
	protected boolean isRouteDisplayed() {
		return false;
	}
    
    private void initLocationData() {
    	// TODO
    	//3.1.1 Initialize LocationManager
    	m_locManager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE); 
    	
//    	3.2.1 Implement LocationListener Interface
    	 m_arrPathPoints = new ArrayList<GeoPoint>();
    	 m_bRecording = false;
    }
    
	private void initLayout() {
    	// TODO
		//2.1 Displaying a Map
		setContentView(R.layout.map_layout);
		m_vwMap = (MapView)findViewById(R.id.m_vwMap);
		m_vwMap.setBuiltInZoomControls(true);
		
		//2.2.1 Display Your Location
		m_locationOverlay = new MyLocationOverlay(this, m_vwMap);
		m_locationOverlay.enableCompass();
		m_locationOverlay.enableMyLocation();
		m_vwMap.getOverlays().add(m_locationOverlay);
				
//		3.3.2 Add a PathOverlay to Your Map
		m_pathOverlay= new PathOverlay(m_arrPathPoints);
		m_vwMap.getOverlays().add(m_pathOverlay);
		if((m_arrPathPoints == null)||(m_bRecording == true))//?
			m_vwMap.postInvalidate();
		Log.i("lab5","??");

    }
	
	private void setRecordingState(boolean bRecording) {
		// TODO
		if(!bRecording){
			m_bRecording = bRecording;
//			LocationListener mlocListener = new LocationListener();
			m_locManager.removeUpdates(this);//pass in the LocationListener that you want to un-register?
		}
		else{
			m_bRecording = bRecording;
			m_arrPathPoints.clear();
			Location location = m_locManager.getLastKnownLocation(
					LocationManager.GPS_PROVIDER);
			onLocationChanged(location);
			m_locManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
					WalkAbout.MIN_TIME_CHANGE,
					WalkAbout.MIN_DISTANCE_CHANGE,this);//??
		}
	}
	
	private void saveRecording() {
		// TODO
		Resources res = getResources();
		String file_name = res.getString(R.string.geoPathFileName);
		
		this.deleteFile(file_name);
		
		FileOutputStream outStream;
		try {
			outStream = this.openFileOutput(file_name,Context.MODE_PRIVATE );
			PrintWriter m_pWriter = new PrintWriter(outStream);
			for(int i=0;i<m_arrPathPoints.size();i++){
				 int lat = (int) (m_arrPathPoints.get(i).getLatitudeE6()/WalkAbout.GEO_CONVERSION);
				 int lon = (int) (m_arrPathPoints.get(i).getLongitudeE6()/WalkAbout.GEO_CONVERSION);
				 m_pWriter.write(Integer.toString(lat));
				 m_pWriter.write(", ");
				 m_pWriter.write(Integer.toString(lon));
				 m_pWriter.write(";");
			}	 
				 Toast.makeText(getApplicationContext(),
							(getResources().getString( R.string.saveSuccess)),
							Toast.LENGTH_SHORT).show();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			
			Toast.makeText(getApplicationContext(),
					(getResources().getString(R.string.saveFailed)),
					Toast.LENGTH_SHORT).show();
			
		};

	}
	
	private void loadRecording() {
		// TODO
		Resources res = getResources();
		String file_name = res.getString(R.string.geoPathFileName);
		
		FileInputStream inStream;
		try {
			inStream = this.openFileInput(file_name);
			Scanner m_scanner = new Scanner(inStream);
			String data = m_scanner.toString();
			for(int i=0 ;i<data.length();i=i+4){
				int lat = data.charAt(i);
				int lon = data.charAt(i+2);
				GeoPoint m_Gpoint = new GeoPoint(lat,lon);
				m_arrPathPoints.add(m_Gpoint);
			}	 
				 Toast.makeText(getApplicationContext(),
							(getResources().getString( R.string.loadSuccess)),
							Toast.LENGTH_SHORT).show();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			
			Toast.makeText(getApplicationContext(),
					(getResources().getString(R.string.loadFailed)),
					Toast.LENGTH_SHORT).show();
			
		};

	}
	
//	2.3 Initialize the WalkAbout Options Menu
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		menu.add(0,WalkAbout.STARTSTOP_MENU_ITEM,Menu.NONE, R.string.startRecording);
		menu.add(0,WalkAbout.SAVE_MENU_ITEM,Menu.NONE, R.string.save);
		menu.add(0,WalkAbout.LOAD_MENU_ITEM,Menu.NONE, R.string.load);
		menu.add(0,WalkAbout.PICTURE_MENU_ITEM,Menu.NONE, R.string.takePicture);
		menu.add(0,WalkAbout.ENABLEGPS_MENU_ITEM,Menu.NONE, R.string.enableGPS);
		return true;}
	
//	3.1.2 Dynamically Update Options Menu
//	The Options menu should display the "Start/Stop" MenuItem as disabled if the GPS Location 
//	Provider is disabled. Additionally, the Options menu should NOT display the "Enable GPS" 
//	MenuItem at all if the GPS Location Provider is enabled
//	 @Override
	 public boolean onPrepareOptionsMenu(Menu menu) {
		 
		 MenuItem item1 = menu.findItem(WalkAbout.STARTSTOP_MENU_ITEM);
		 MenuItem item2 = menu.findItem(WalkAbout.ENABLEGPS_MENU_ITEM);
		 MenuItem item3 = menu.findItem(WalkAbout.PICTURE_MENU_ITEM);
		 MenuItem item4 = menu.findItem(WalkAbout.SAVE_MENU_ITEM);
		 MenuItem item5 = menu.findItem(WalkAbout.LOAD_MENU_ITEM);
		 
		 if(m_locManager.isProviderEnabled(LocationManager.GPS_PROVIDER)){
			 item1.setEnabled(true);
			 item2.setEnabled(false);
		 }
		 else{
			 item1.setEnabled(false);
			 item2.setEnabled(true);
			 			 
//			 3.1.3 Implement "Enable  GPS" MenuItem
			 item2.setOnMenuItemClickListener(new OnMenuItemClickListener(){
				 public boolean onMenuItemClick(MenuItem item){
					 Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
					 startActivityForResult(intent,WalkAbout.ENABLE_GPS_REQUEST_CODE);
					 return true;
				 }
			 }); 
		 }
		 
//		 3.2.2 Dynamically Update the "Start/Stop" MenuItem Text
		 if(m_bRecording == true){
			item1.setTitle(R.string.stopRecording);
		 	item3.setEnabled(true);
		 }
		 else{
			item1.setTitle(R.string.startRecording);
			item3.setEnabled(false);
		 }
		 Log.i("lab5","a");
		 
//		 3.2.3 Implement "Start/Stop" MenuItem
		 item1.setOnMenuItemClickListener(new OnMenuItemClickListener(){
			@Override
			public boolean onMenuItemClick(MenuItem item) {
				// TODO Auto-generated method stub
				if(m_bRecording == false)
					setRecordingState(true);
				else
					setRecordingState(false);
				return true;
			}
			 
		 });
		 
		 
//		 4.1.2 Launch the CameraPreview Activity
		 item3.setOnMenuItemClickListener(new OnMenuItemClickListener(){
			 public boolean onMenuItemClick(MenuItem item){
				 Intent intent = new Intent(WalkAbout.this,CameraPreview.class);
				 startActivityForResult(intent,WalkAbout.PICTURE_REQUEST_CODE);
				 return true;
			 }
		 }); 
		 


//		 5.1 Creating, Writing, & Deleting Files
		 item4.setOnMenuItemClickListener(new OnMenuItemClickListener(){
			 public boolean onMenuItemClick(MenuItem item){
				 saveRecording();
				 return true;
			 }
		 }); 
		 
//		 5.2 Reading File
		 item5.setOnMenuItemClickListener(new OnMenuItemClickListener(){
			 public boolean onMenuItemClick(MenuItem item){
				 m_bRecording = false;
				 loadRecording();
				 return true;
			 }
		 }); 
		 
		 return super.onPrepareOptionsMenu(menu);
	 }
	  

//
//	 3.2.1 Implement LocationListener Interface
//	 •Record location changes in the onLocationChanged(...) method.
	 @Override
	 public void onLocationChanged(Location arg0) {
		 // TODO Auto-generated method stub
		double latitude = arg0.getLatitude()*(WalkAbout.GEO_CONVERSION);
		double longitude = arg0.getLongitude() * (WalkAbout.GEO_CONVERSION);
		GeoPoint myGeoPoint = new GeoPoint((int)latitude, (int)longitude);
		m_arrPathPoints.add(myGeoPoint);
		
//		3.2.4 Center MapView on Current Location
		m_mapController = m_vwMap.getController();
		m_mapController.animateTo(myGeoPoint);
		m_mapController.setZoom(17);
		Log.i("lab5", "onLocationChaged: Loction-"+myGeoPoint.toString()+" N-"+m_arrPathPoints.size());
		
//		test
//		Context context = getApplicationContext();
//		CharSequence text = (CharSequence) arg0;
//		int duration = Toast.LENGTH_SHORT;
//		Toast toast = Toast.makeText(context, text, duration);toast.show();
	 }
	 
//	 •In the onProviderDisabled(...) method, instruct the
//	 	WalkAbout Activity to stop recording location changes
	 @Override
	 public void onProviderDisabled(String arg0) {
		 // TODO Auto-generated method stub
		 setRecordingState(false);
	
	 }
	 @Override
	public void onProviderEnabled(String arg0) {
		 // TODO Auto-generated method stub
	
	 }
	 @Override
	public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
		 // TODO Auto-generated method stub
	}
	
//???????????????????????????????????????????????????????????????????????	 
//	 3.1.4 Handle the Location Settings Activity Result
	 @Override
	 protected void onActivityResult(int requestCode, int resultCode, Intent data){
		 super.onActivityResult(requestCode, resultCode, data);
		 if(requestCode == WalkAbout.ENABLE_GPS_REQUEST_CODE){
			 m_locationOverlay = new MyLocationOverlay(this, m_vwMap);
				m_locationOverlay.enableCompass();
				m_locationOverlay.enableMyLocation();
				m_vwMap.getOverlays().add(m_locationOverlay);
		 }
		 else if(requestCode == WalkAbout.PICTURE_REQUEST_CODE){
				if (resultCode == Activity.RESULT_CANCELED){
					Toast.makeText(getApplicationContext(),R.string.pictureFail,
							Toast.LENGTH_SHORT).show();
				}
				if (resultCode == Activity.RESULT_OK){
					Toast.makeText(getApplicationContext(),
							(getResources().getString(R.string.pictureSuccess) + "/"+"\n"
							+ data.getExtras().getString(CameraPreview.IMAGE_FILE_NAME)),
//									),
							Toast.LENGTH_SHORT).show();
				}	
			}
		 else return;
	 }
	 
}