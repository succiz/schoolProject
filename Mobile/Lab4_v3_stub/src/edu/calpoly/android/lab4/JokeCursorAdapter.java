package edu.calpoly.android.lab4;

import android.content.Context;
import android.database.Cursor;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.CursorAdapter;
import android.widget.AdapterView.OnItemLongClickListener;
import edu.calpoly.android.lab4.JokeView.OnJokeChangeListener;

public class JokeCursorAdapter extends CursorAdapter implements OnItemLongClickListener {

	/**
	 * The ID of the currently selected Joke.
	 */
	private long m_nSelectedID;

	/**
	 * The OnJokeChangeListener that should be connected to each of the
	 * JokeViews created/managed by this Adapter.
	 */
	private OnJokeChangeListener m_listener;

	/**
	 * Parameterized constructor that takes in the application Context in which
	 * it is being used and the Collection of Joke objects to which it is bound.
	 * m_nSelectedPosition will be initialized to Adapter.NO_SELECTION.
	 * 
	 * @param context
	 *            The application Context in which this JokeListAdapter is being
	 *            used.
	 * 
	 * @param jokeCursor
	 *            A Database Cursor containing a result set of Jokes which
	 *            should be bound to JokeViews.
	 */
	public JokeCursorAdapter(Context context, Cursor jokeCursor) {
		super(context, jokeCursor);
		
		m_nSelectedID = Adapter.NO_SELECTION;
		m_listener = null;
		// TODO
	}

	/**
	 * Accessor method for retrieving the position in the dataset of the
	 * currently selected Joke.
	 * 
	 * @return an integer representing the position in the dataset of the
	 *         currently selected Joke.
	 */
	public long getSelectedID() {
		// TODO
		return m_nSelectedID;
	}

	/**
	 * @param listener
	 *            The OnJokeChangeListener that will be notified when the
	 *            internal state of any Joke contained in one of this Adapters
	 *            JokeViews is changed.
	 */
	public void setOnJokeChangeListener(OnJokeChangeListener mListener) {
		// TODO
		m_listener = mListener;
	}

	@Override
	public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
		// TODO
		m_nSelectedID = id;
		return false;
	}

	@Override
	public void bindView(View view, Context context, Cursor cursor) {
		// TODO Auto-generated method stub
		Joke myJoke = JokeDBAdapter.getJokeFromCursor(cursor);
		((JokeView) view).setJoke(myJoke);
		
		
	}

	@Override
	public View newView(Context context, Cursor cursor, ViewGroup parent) {
		// TODO Auto-generated method stub
		
		Joke myJoke = JokeDBAdapter.getJokeFromCursor(cursor);	
		JokeView myJokeView = new JokeView(context,myJoke);
		myJokeView.setOnJokeChangeListener(m_listener);
		return null;
	}
}