package szhao.bluetooth;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;

public class DeviceView extends LinearLayout{

	private Device m_device;
	
	public DeviceView(Context context, Device device) {
		super(context);
		// TODO Auto-generated constructor stub
		LayoutInflater inflater = (LayoutInflater) context
		.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		inflater.inflate(R.layout.device_view, this, true);
		m_device = device;
		initLayout();
	}
		
	private void initLayout() {
		TextView deviceName = (TextView)findViewById(R.id.deviceName);
		deviceName.setText(m_device.getName());
		if(m_device.isConnection()){
			if(!m_device.isRemind())
				deviceName.setBackgroundColor(Color.GREEN);
			else
				deviceName.setBackgroundColor(Color.YELLOW);
		}
		else{
			if(m_device.isRemind())
				deviceName.setBackgroundColor(Color.RED);
		}
			
	}
	
	public Device getDevice() {
		return m_device;
	}
	
	public void setDevice(Device device) {
		m_device = device;
		initLayout();
		postInvalidate();
	}

}
