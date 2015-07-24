package szhao.bluetooth;

import java.util.List;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.BaseAdapter;

public class DeviceAdapter extends BaseAdapter {
	
	/**
	 * The application Context in which this deviceAdapter is being used.
	 */
	private Context m_context;

	/**
	 * The dataset to which this deviceAdapter is bound.
	 */
	private List<Device> m_deviceList;

	/**
	 * The position in the dataset of the currently selected Device.
	 */
	private int m_nSelectedPosition;

	/**
	 * Parameterized constructor that takes in the application Context in which
	 * it is being used and the Collection of Device objects to which it is bound.
	 * m_nSelectedPosition will be initialized to Adapter.NO_SELECTION.
	 * 
	 * @param context
	 *            The application Context in which this JokeListAdapter is being
	 *            used.
	 * 
	 * @param jokeList
	 *            The Collection of Joke objects to which this JokeListAdapter
	 *            is bound.
	 */
	public DeviceAdapter(Context context, List<Device> deviceList) {
		m_context = context;
		m_deviceList = deviceList;
		m_nSelectedPosition = Adapter.NO_SELECTION;
	}

	/**
	 * Accessor method for retrieving the position in the dataset of the
	 * currently selected Joke.
	 * 
	 * @return an integer representing the position in the dataset of the
	 *         currently selected Joke.
	 */
	public int getSelectedPosition() {
		return m_nSelectedPosition;
	}

	@Override
	public int getCount() {

		return m_deviceList.size();
	}

	@Override
	public Object getItem(int position) {
		return m_deviceList.get(position);
	}
	
	public Object getItem(String name) {
		int pos = 0;
		for(int i=0;i<m_deviceList.size();i++){
		    if(m_deviceList.get(i).getName().equals(name))
		    	pos = i;
		    else pos = -1;
		}
		if(pos!=-1)
			return m_deviceList.get(pos);
		else
			return null;
	}

	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		DeviceView m_deviceview = null;
		 if(convertView == null){
			 m_deviceview = new DeviceView(m_context,m_deviceList.get(position));
		 }
		 else{ 
			 m_deviceview = (DeviceView)convertView;
			 m_deviceview.setDevice(m_deviceList.get(position));//?
		 }
		return m_deviceview;
	}

}
