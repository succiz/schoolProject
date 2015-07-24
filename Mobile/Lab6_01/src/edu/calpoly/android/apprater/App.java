package edu.calpoly.android.apprater;

public class App {

	private String m_strAppName;
	private String m_strInstallURI;
	private int m_nRating;
	private long m_nID;
	private boolean m_bInstalled;
	
	public static final long NO_ID = -1l;
	public static final int UNRATED = -1;
	
	public App(String appName, String installURI, int rating, long id, boolean installed) {
		super();
		m_strAppName = appName;
		m_strInstallURI = installURI;
		m_nRating = rating;
		m_nID = id;
		m_bInstalled = installed;
	}
	
	public App(String appName, String installURI) {
		super();
		m_strAppName = appName;
		m_strInstallURI = installURI;
		m_nRating = UNRATED;
		m_nID = NO_ID;
		m_bInstalled = false;
	}
	
	public int getRating() {
		return m_nRating;
	}
	public void setRating(int rating) {
		m_nRating = rating;
	}
	
	public boolean isInstalled() {
		return m_bInstalled;
	}
	public void setInstalled(boolean installed) {
		m_bInstalled = installed;
	}
	
	public long getID() {
		return m_nID;
	}
	public void setID(long id) {
		m_nID = id;
	}
	
	public String getName() {
		return m_strAppName;
	}
	public String getInstallURI() {
		return m_strInstallURI;
	}
}
