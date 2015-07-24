package edu.calpoly.android.apprater;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.net.Uri;

public class AppContentProvider extends ContentProvider {

	/*****************/
	/** STATIC DATA **/
	/*****************/
	
	/** Database information **/
	private static final String DATABASE_NAME = "Key_AppListDatabase.db";
	private static final int DATABASE_VERSION = 2;

	/** App table information **/
	private static final String DATABASE_TABLE_APP = "tbl_apps";
	
	/**
	 * This column has a value type of integer and corresponds to the App.m_nID
	 * member variable. 
	 */
	public static final String APP_KEY_ID = "_id";
	public static final int APP_COL_ID = 0;

	/**
	 * This column has a value type of String and corresponds to the
	 * App.m_strAppName member variable.
	 */
	public static final String APP_KEY_NAME = "name";
	public static final int APP_COL_NAME = APP_COL_ID + 1;

	/**
	 * This column has a value type of integer and corresponds to the
	 * App.m_nRating member variable.
	 */
	public static final String APP_KEY_RATING = "rating";
	public static final int APP_COL_RATING = APP_COL_ID + 2;

	/**
	 * This column has a value type of String and corresponds to the
	 * App.m_strInstallURI member variable.
	 */
	public static final String APP_KEY_INSTALLURI = "install_uri";
	public static final int APP_COL_INSTALLURI = APP_COL_ID + 3;

	/**
	 * This column has a value type of integer and corresponds to the
	 * App.m_bInstalled member variable.
	 * 
	 * This value of this column should be 0 if the App.m_bInstalled is false
	 * and 1 if App.m_bInstalled is true.
	 */
	public static final String APP_KEY_INSTALLED = "installed";
	public static final int APP_COL_INSTALLED = APP_COL_ID + 4;

	/** URI Constants **/
	public static final Uri CONTENT_URI = Uri.parse("content://edu.calpoly.android.provider.apprater/apps");
	private static final int ALL_APPS = 1;
	private static final int APP_ID = ALL_APPS + 1;
	private static final UriMatcher s_uriMacther = new UriMatcher(UriMatcher.NO_MATCH);

	/**
	 * Database of Apps that the ContentProvider interfaces with.
	 */
	private SQLiteDatabase m_appDB;
	
	/**
	 * Initialize your SQLiteDatabase here. Make sure to return the correct boolean value.
	 */
	@Override
	public boolean onCreate() {
		// TODO
		return false;
	}

	/**
	 * Don't worry about this method, you can leave this as it is for now.
	 */
	@Override
	public String getType(Uri uri) {
		return "";
	}

	/**
	 * This method is like the JokeDBAdapter.getAllJokes(...) method from Lab4.
	 */
	@Override
	public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
		// TODO		
		return null;
	}
	
	/**
	 * This method is like the JokeDBAdapter.insertJoke(...) method from Lab4.
	 */
	@Override
	public Uri insert(Uri uri, ContentValues values) {
		// TODO		
		return null;
	}
	
	/**
	 * This method is like the JokeDBAdapter.removeJoke(...) method from Lab4.
	 */
	@Override
	public int delete(Uri uri, String selection, String[] selectionArgs) {
		return 0;
	}

	/**
	 * This method is like the JokeDBAdapter.updateJoke(...) method from Lab4.
	 */
	@Override
	public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
		// TODO		
		return 0;
	}	
		
	/**
	 * If you can't remember how to fill this class in see Lab 4.
	 */
	public static class AppDBHelper extends SQLiteOpenHelper {
		/** Database SQL **/
		public static final String DATABASE_CREATE = "create table " + DATABASE_TABLE_APP + " (" + 
				APP_KEY_ID + " integer primary key autoincrement, " + 
				APP_KEY_NAME	+ " text not null unique, " + 
				APP_KEY_RATING	+ " integer not null, " + 
				APP_KEY_INSTALLURI + " text not null unique, " + 
				APP_KEY_INSTALLED + " integer not null );";
		
		public static final String DATABASE_DROP = "drop table if exists " + DATABASE_TABLE_APP;
		
		public AppDBHelper(Context context, String name, CursorFactory factory, int version) {
			super(context, name, factory, version);
		}

		@Override
		public void onCreate(SQLiteDatabase _db) {
			// TODO		
		}

		@Override
		public void onUpgrade(SQLiteDatabase _db, int _oldVersion, int _newVersion) {
			// TODO		
		}
	}
}
