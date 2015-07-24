package szhao.bluetooth;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.Spinner;

public class AppSetting extends Activity implements OnClickListener {
	
	private CheckBox sound;
	private Spinner timer;
	private Spinner background;
	private Button ok;
	private Button cancel;
	private LinearLayout linearLayout02;
	private boolean isSound;
	private int position1;
	private int position2;
	private int time;
	private int image;
	
	public static final String CHECKED_SOUND_VALUE = "isSound";
	public static final String CHECKED_TIME_VALUE = "time";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.setting);
//		Get saved preference
		isSound =  this.getIntent().getExtras().getBoolean(
				BluetoothReminder.SAVED_SOUND_VALUE);
		time= this.getIntent().getExtras().getInt(
				BluetoothReminder.SAVED_TIME_VALUE);
		image= this.getIntent().getExtras().getInt(
				BluetoothReminder.SAVED_IMAGE_VALUE);
		Log.i("test","pass in:"+image);
		
//		initial layout
		linearLayout02 = (LinearLayout)findViewById(R.id.linearLayout02);
        linearLayout02.setBackgroundResource(image);
        
		sound = (CheckBox)findViewById(R.id.sound);
		timer = (Spinner)findViewById(R.id.time);
		background = (Spinner)findViewById(R.id.background);
		ok = (Button)findViewById(R.id.ok);
		ok.setOnClickListener(this);
		cancel = (Button)findViewById(R.id.cancel);
		cancel.setOnClickListener(this);
	
	    int[] timeValues = 
	    	  getResources().getIntArray(R.array.displayValues);
		for(int i=0;i<timeValues.length;i++){
			if(timeValues[i]==time)
				position1 = i;
		 }
		
		int[] imageValues = 
		    getResources().getIntArray(R.array.imageValues);
		for(int j=0;j<imageValues.length;j++){
			if(imageValues[j]==image)
				position2 = j;
			Log.i("test","position2:"+position2);
		}
			
		
		//initial spinner
		ArrayAdapter<CharSequence> adapter1 = 
			ArrayAdapter.createFromResource(this, 
				R.array.displayItem, android.R.layout.simple_spinner_item);
		adapter1.setDropDownViewResource
		         (android.R.layout.simple_spinner_dropdown_item);
		timer.setAdapter(adapter1);
		//initial spinner
		ArrayAdapter<CharSequence> adapter2 = 
			ArrayAdapter.createFromResource(this, 
				R.array.imageNames, android.R.layout.simple_spinner_item);
		adapter2.setDropDownViewResource
		         (android.R.layout.simple_spinner_dropdown_item);
		background.setAdapter(adapter2);
		
		sound.setChecked(isSound);
//		if(time != 0)
//			timer.isChecked(false);
//		}
		timer.setSelection(position1);
		background.setSelection(position2);
	}
	
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if(v.getId() == R.id.ok){	        
			updateSetting();
			finish();
		}
		else if(v.getId() == R.id.cancel){
			setResult(RESULT_CANCELED,null);
			finish();
		}
		else return;
	}
	
	public void updateSetting(){
		
		isSound = sound.isChecked();
		position1 = timer.getSelectedItemPosition();
		position2 = background.getSelectedItemPosition();
		Log.i("test","position:"+position2);
	    int[] timeValues = 
	    	  getResources().getIntArray(R.array.displayValues);
	    time = timeValues [position1];
	    int[] imageValues = 
	    	  getResources().getIntArray(R.array.imageValues);
	    image = imageValues [position2];
	    Log.i("test","in setting:"+time);
        linearLayout02 = (LinearLayout)findViewById(R.id.linearLayout02);
        switch(position2){
        case 0: linearLayout02.setBackgroundResource(R.drawable.background01);
        break;
        case 1:linearLayout02.setBackgroundResource(R.drawable.background02);
        break;
        case 2:linearLayout02.setBackgroundResource(R.drawable.background03);
        break;
        default: break;
        }
		Intent intent = new Intent();
		intent.putExtra(CHECKED_SOUND_VALUE,isSound);
		intent.putExtra(CHECKED_TIME_VALUE,time);
		intent.putExtra(BluetoothReminder.SAVED_IMAGE_VALUE,image);
		setResult(RESULT_OK, intent);		
	}
	
}
