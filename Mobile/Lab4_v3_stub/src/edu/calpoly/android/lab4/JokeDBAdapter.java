package edu.calpoly.android.lab4;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.util.Log;

public class JokeDBAdapter {

	/*****************/
	/** STATIC DATA **/
	/*****************/
	
	/** Database information **/
	public static final String DATABASE_NAME = "JokeListDatabase.db";
	public static final int DATABASE_VERSION = 1;

	/** Joke table information **/
	public static final String DATABASE_TABLE_JOKE = "tbl_jokes";

	public static final String JOKE_KEY_ID = "_id";
	public static final int JOKE_COL_ID = 0;

	public static final String JOKE_KEY_TEXT = "joke_text";
	public static final int JOKE_COL_TEXT = JOKE_COL_ID + 1;

	public static final String JOKE_KEY_RATING = "rating";
	public static final int JOKE_COL_RATING = JOKE_COL_ID + 2;

	public static final String JOKE_KEY_AUTHOR = "author";
	public static final int JOKE_COL_AUTHOR = JOKE_COL_ID + 3;

	/** Database SQL **/
	public static final String DATABASE_CREATE = "create table " + DATABASE_TABLE_JOKE + " (" + 
			JOKE_KEY_ID + " integer primary key autoincrement, " + 
			JOKE_KEY_TEXT	+ " text not null, " + 
			JOKE_KEY_RATING	+ " integer not null, " + 
			JOKE_KEY_AUTHOR + " text not null);";
	
	public static final String DATABASE_DROP = "drop table if exists " + DATABASE_TABLE_JOKE;

	/** Joke table SQL **/


	/*******************/
	/** INSTANCE DATA **/
	/*******************/
	
	/** Database Instance **/
	private SQLiteDatabase m_db;
		
	/** Database open/upgrade helper **/
	private JokeDBHelper m_dbHelper;
	
	/**
	 * Parameterized Constructor
	 * 
	 * @param context 
	 * 			  The application Context in which this JokeDBAdapter is being
	 * 			  used.
	 */
	public JokeDBAdapter(Context context) {
		// TODO
		m_dbHelper = new JokeDBHelper(context,JokeDBAdapter.DATABASE_NAME,null,JokeDBAdapter.DATABASE_VERSION);
	}
	
	/**
	 * Initializes the underlying SQLiteDatabase object for Writable access.
	 */
	public void open() {
		// TODO
		m_db = m_dbHelper.getWritableDatabase();
	}
	
	/**
	 * Closes the underlying SQLiteDatabse object.
	 */
	public void close() {
		// TODO
		m_db.close(); 
	}
	
	/**
	 * Inserts a Joke object into the Database.
	 * 
	 * @param joke
	 * 			  The Joke object which to be persisted in the Database.
	 * 
	 * @return The row ID of the newly inserted row, or -1 if an error 
	 * 		   occurred.
	 */
	public long insertJoke(Joke joke) {
		// TODO
		ContentValues myContentValues = new ContentValues();
		myContentValues.put(JokeDBAdapter.JOKE_KEY_TEXT,joke.getJoke());//????????????????
		myContentValues.put(JokeDBAdapter.JOKE_KEY_RATING,joke.getRating());
		myContentValues.put(JokeDBAdapter.JOKE_KEY_AUTHOR,joke.getAuthor());
		return m_db.insert(DATABASE_TABLE_JOKE,null,myContentValues);

	}
	
	/**
	 * Returns a Cursor containing all Joke rows in the Database that have a 
	 * rating equal to ratingFilter.
	 * 
	 * If ratingFilter is null the returned Cursor should contain all Joke rows
	 * in the Database.
	 * 
	 * @param ratingFilter
	 * 			  A String containing only the rating value. The rating value 
	 * 			  must contain one of Joke.LIKE, Joke.DISLIKE, Joke.UNRATED, or
	 * 			  be null. 
	 * 
	 * @return A Cursor containing rows in the Database Joke Table whose rating
	 * 		   matches ratingFilter, or all rows if ratingFilter is null. 
	 */

	public Cursor getAllJokes(String ratingFilter) {
		// TODO
		String local; 
		if(ratingFilter == null){
			local = null;
			return m_db.query (JokeDBAdapter.DATABASE_TABLE_JOKE, new String[]{JokeDBAdapter.JOKE_KEY_ID, JokeDBAdapter.JOKE_KEY_TEXT, JokeDBAdapter.JOKE_KEY_RATING,JokeDBAdapter.JOKE_KEY_AUTHOR},null, 
					null, null,null,null);//????????????????????????????????????????????????
		}
		else{
			local = JOKE_KEY_RATING + "=" + ratingFilter;		
		return m_db.query (JokeDBAdapter.DATABASE_TABLE_JOKE, new String[]{JokeDBAdapter.JOKE_KEY_ID, JokeDBAdapter.JOKE_KEY_TEXT, JokeDBAdapter.JOKE_KEY_RATING,JokeDBAdapter.JOKE_KEY_AUTHOR},local, 
				null, null,null,null);
		}
	}
	
	/**
	 * Returns a Cursor containing all Joke rows in the Database.
	 * 
	 * @return A Cursor containing all rows in the Database Joke Table.
	 */
	public Cursor getAllJokes() {
		// TODO
		return  getAllJokes(null);
	}
	
	/**
	 * This method constructs a Joke object using the data from a row in the 
	 * Joke Database Table pointed to by the Cursor passed in.
	 * 
	 * If the cursor is null or empty, the method should return null.
	 * 
	 * @param cursor
	 * 			  A Cursor pointing to a row in the Joke Database Table.
	 * 
	 * @return A Joke object containing the data pointed to by the Cursor 
	 * 		   object passed in, or null if the Cursor is empty or null.
	 */
	public static Joke getJokeFromCursor(Cursor cursor) {
		// TODO
		if(cursor.getCount()==0||!cursor.moveToFirst())//???????????
			return null;
		long id = cursor.getLong(JOKE_COL_ID);
		String text = cursor.getString(JOKE_COL_TEXT);
		String author = cursor.getString(JOKE_COL_AUTHOR);
		int rating = cursor.getInt(JOKE_COL_RATING);
		Joke myJoke = new Joke(text,author,rating,id);
		return myJoke;
		
	}
	
	/**
	 * Retrieves a row from the Joke Database table whose _id matches the "id"
	 * parameter passed in. A Joke is then constructed and initialized using 
	 * the information contained in the Database row.
	 *   
	 * @param id
	 * 			  The id of the Joke to retrieve from the Database. 
	 * 
	 * @return A Joke object containing the data in the Joke Database Table row
	 * 		   whose _id matches the "id" parameter. 
	 */
	public Joke getJoke(long id) {
		// TODO
		Cursor cursor = m_db.query(JokeDBAdapter.DATABASE_TABLE_JOKE, new String[]
		                          {JokeDBAdapter.JOKE_KEY_ID, JokeDBAdapter.JOKE_KEY_TEXT, JokeDBAdapter.JOKE_KEY_RATING,
				                   JokeDBAdapter.JOKE_KEY_AUTHOR},JOKE_KEY_ID + "="+id, null, null,null,null);//????????????????????????
		cursor.moveToNext();
		long myID = cursor.getLong(JOKE_COL_ID);
		String text = cursor.getString(JOKE_COL_TEXT);
		String author = cursor.getString(JOKE_COL_AUTHOR);
		int rating = cursor.getInt(JOKE_COL_RATING);//??????????????????????????????
		Joke myJoke = new Joke(text,author,rating,myID);
		return myJoke;
	}	
	
	/**
	 * Removes a Joke object from the Database.
	 * 
	 * @param id
	 * 			  The id of the Joke to remove from the Database.
	 * 
	 * @return True if a row in the database with an _id equaling 'id' was 
	 * 		   found and removed; False otherwise. 
	 */
	public boolean removeJoke(long id) {		
		// TODO
		String string = JOKE_KEY_ID + "="+id;
		int count = m_db.delete(DATABASE_TABLE_JOKE , string,null);
		if(count != 0)
			return true;
		else return false;
	}
	
	/**
	 * Updates the contents of a Joke in the Database. Will write the data 
	 * contained in the Joke passed in back to the Database. 
	 * 
	 * @param joke
	 * 			  The Joke containing data to write back to the database.
	 * 
	 * @return True if a row in the database with an _id equaling Joke.getID()
	 * 		   was found and updated; False otherwise. 
	 * 
	 */
	public boolean updateJoke(Joke joke) {
		// TODO
		ContentValues myContentValues = new ContentValues();
		myContentValues.put(JokeDBAdapter.JOKE_KEY_TEXT,joke.getJoke());//????????????????
		myContentValues.put(JokeDBAdapter.JOKE_KEY_RATING,joke.getRating());
		myContentValues.put(JokeDBAdapter.JOKE_KEY_AUTHOR,joke.getAuthor());
		String string = JOKE_KEY_ID + "=" + joke.getID();
		int count;
		count = m_db.update(DATABASE_TABLE_JOKE , myContentValues, string, null);
		if(count!=0)
			return true;
		else return false;
	}

	/**
	 * Helper class used to wrap the logic necessary for Creating and Upgrading
	 * the underlying SQLiteDatabase that JokeDBAdapter relies on.
	 */
	private static class JokeDBHelper extends SQLiteOpenHelper {

		/**
		 * Parameterized constructor. Should only call its super version of 
		 * this constructor, passing in all the parameters it is given.
		 */
		public JokeDBHelper(Context context, String name, CursorFactory factory, int version) {
			super(context, name, factory, version);
		}

		/**
		 * Called when the Database is created for the first time.
		 */
		@Override
		public void onCreate(SQLiteDatabase _db) {
			// TODO
			_db.execSQL(JokeDBAdapter.DATABASE_CREATE);


		}

		/**
		 * Called when the Constructor is called with a version number that 
		 * differs from the current Database version.
		 * 
		 * This method is used to perform upgrades to the existing database. 
		 * If you should have to upgrade the database, this is where you could
		 * save data currently in the database before migrating to the new 
		 * schema. 
		 */
		@Override
		public void onUpgrade(SQLiteDatabase _db, int _oldVersion, int _newVersion) {
			// TODO
			_db.execSQL(JokeDBAdapter.DATABASE_DROP);
			onCreate(_db);
		}

	}
}
