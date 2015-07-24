package edu.calpoly.android.apprater;

import edu.calpoly.android.appraterkey.AppContentProvider;
import android.content.Context;
import android.database.Cursor;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.CursorAdapter;

public class AppCursorAdapter extends CursorAdapter{

	public AppCursorAdapter(Context context, Cursor cursor) {
		super(context, cursor);
	}

	/**
	 * Reset the AppView argument to use the App data pointed to by the Cursor.
	 */
	@Override
	public void bindView(View view, Context context, Cursor cursor) {
		((AppView)view).setApp(getAppFromCursor(cursor));
	}

	/**
	 * Construct a new AppView for the App data pointed to by the Cursor.
	 */
	@Override
	public View newView(Context context, Cursor cursor, ViewGroup parent) {
		AppView view = new AppView(context, getAppFromCursor(cursor));
		return view;
	}

	/**
	 * This method constructs an App object using the data pointed to by the Cursor passed in.
	 * 
	 * If the cursor is null or empty, the method should return null.
	 * 
	 * @param cursor
	 * 			  A Cursor pointing at the from which an App object should be constructed.
	 * 
	 * @return An App object containing the data pointed to by the Cursor 
	 * 		   object passed in, or null if the Cursor is empty or null.
	 */
	public static App getAppFromCursor(Cursor cursor) {
		if (cursor == null || cursor.getCount() == 0) {
			return null;
		}
		
		return new App(cursor.getString(AppContentProvider.APP_COL_NAME),
					   cursor.getString(AppContentProvider.APP_COL_INSTALLURI),
					   cursor.getInt(AppContentProvider.APP_COL_RATING),
					   cursor.getLong(AppContentProvider.APP_COL_ID),
					   cursor.getInt(AppContentProvider.APP_COL_INSTALLED) != 0);
	}

//	@Override
//	public void onItemClick(AdapterView<?> arg0, View arg1, int position, long id) {
//		// TODO Auto-generated method stub
////		App myApp = getAppFromCursor();
//		Intent intent = new Intent();
//	}
}
