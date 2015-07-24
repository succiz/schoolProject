package szhao.bluetooth;

import android.bluetooth.BluetoothDevice;

public class Device{
	/** Contains the name of this device **/
	private boolean m_connection;
	private BluetoothDevice m_device;
	private boolean m_operation;

	public static final int REMINDE = 1;
//	public static final int IGNORE = 2;
	/**
	 * Initializes with the device and empty address strings passed in 
	 * @param strDevice
	 *            Device String used to initialize the name of this device.
	 * 
	 * @return 
	 */
	public Device(BluetoothDevice device) {
		m_device = device;
		m_operation = false;
		m_connection = false;
	}

//	/**
//	 * Initializes with the device and address strings passed in
//	 * 
//	 * @param strDevice
//	 *            Device String used to initialize the text of this device.
//	 * 
//	 * @param strAddress
//	 *            The address of this Device.
//	 * @return 
//	 */
//	public Device(String strDevice, String strAddress) {
//		m_strDevice = strDevice;
//	}

	/**
	 * Accessor for the name of this device.
	 * 
	 * @return A String value containing the name of this device.
	 */
	public String getName() {
		return m_device.getName();
	}
	
	/**
	 * Accessor for the operation of this device.
	 * 
	 * @return An integer value containing one of the possible operation constants.
	 */
	public boolean isRemind() {
		return m_operation;
	}

	/**
	 * Mutator that changes the operation of this device.
	 * 
	 * @param rating
	 *            One of the possible operation constants.
	 */
	public void setOperation(boolean operation) {
		m_operation = operation;
	}
	
	public boolean isConnection(){
		return m_connection;
	}
	
	public void setConnection(boolean connection){
		m_connection = connection;
	}

	/**
	 * Mutator that changes the name of this device.
	 * 
	 * @param strDevice
	 *            The name of this device.
	 */
//	public void setName(String strDevice) {
//		m_strDevice = strDevice;
//	}

	/**
	 * Accessor for the address of this device.
	 * 
	 * @return An string containing the address.
	 */
//	public String getAddress() {
//		return m_strAddress;
//	}

	/**
	 * Mutator that address of this device.
	 * 
	 * @param address
	 *            
	 */
//	public void setAddress(String address) {
//		m_strAddress = address;
//	}

	/**
	 * Returns only the name of the device.
	 * 
	 * @return A string containing the name of the device
	 */
//	@Override
//	public String toString() {
//		return m_strDevice;
//	}

}

