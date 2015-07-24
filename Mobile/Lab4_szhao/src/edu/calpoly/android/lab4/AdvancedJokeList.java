package edu.calpoly.android.lab4;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Scanner;

import edu.calpoly.android.lab4.JokeView.OnJokeChangeListener;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.database.Cursor;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.ContextMenu;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;


public class AdvancedJokeList extends Activity implements JokeView.OnJokeChangeListener {

	/**
	 * Contains the name of the Author for the jokes.
	 */
	protected String m_strAuthorName;

	/**
	 * Contains the list of Jokes the Activity will present to the user.
	 **/
	protected Cursor m_arrJokeList;
	protected ArrayList<Joke> m_arrFilteredJokeList;

	/**
	 * Adapter used to bind an AdapterView to List of Jokes.
	 */
	protected JokeCursorAdapter m_jokeAdapter;

	/**
	 * ViewGroup used for maintaining a list of Views that each display Jokes.
	 **/
	protected ListView m_vwJokeLayout;

	/**
	 * EditText used for entering text for a new Joke to be added to
	 * m_cursorJokeList.
	 **/
	protected EditText m_vwJokeEditText;

	/**
	 * Button used for creating and adding a new Joke to m_cursorJokeList using the
	 * text entered in m_vwJokeEditText.
	 **/
	protected Button m_vwJokeButton;
	
	/**
	 * Database of Jokes the user can view, add to, and remove from.
	 */
	protected JokeDBAdapter m_jokeDB;
		
	/**
	 * Context-Menu MenuItem ID's
	 * IMPORTANT: You must use these when creating your MenuItems or the tests
	 * used to grade your submission will fail.
	 */
	protected static final int REMOVE_JOKE_MENUITEM = Menu.FIRST;
	protected static final int UPLOAD_JOKE_MENUITEM = Menu.FIRST + 1;

	/**
	 * Value used to filter which jokes get displayed to the user.
	 */
	protected int m_nFilter;

	/**
	 * Key used for storing and retrieving the value of m_nFilter in 
	 * savedInstanceState.
	 */
	protected static final String SAVED_FILTER_VALUE = "m_nFilter";

	/**
	 * Key used for storing and retrieving the text in m_vwJokeEditText in 
	 * savedInstanceState.
	 */
	protected static final String SAVED_EDIT_TEXT = "m_vwJokeEditText";
	private SharedPreferences mySP;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Initialize the ContentView
		initLayout();

		// Initialize Author Name
		Resources res = getResources();
		m_strAuthorName = res.getString(R.string.author_name);
		m_jokeDB = new JokeDBAdapter(this);
		m_jokeDB.open();

		m_arrJokeList = m_jokeDB.getAllJokes();
		startManagingCursor(m_arrJokeList);
		
		// Initialize the list of jokes from the strings.xml resource file
		m_nFilter = R.id.show_all_menuitem;
//		m_arrFilteredJokeList = new ArrayList<Joke>();

//		3.3.1 Initializing JokeDBAdapter, JokeCursorAdapter, & Cursor

		m_jokeAdapter = new JokeCursorAdapter(this, m_arrJokeList);
		m_jokeAdapter.setOnJokeChangeListener(this); 
		
		m_vwJokeLayout.setAdapter(m_jokeAdapter);
		m_vwJokeLayout.setOnItemLongClickListener(m_jokeAdapter);
		registerForContextMenu(m_vwJokeLayout);
		
		String text = PreferenceManager.getDefaultSharedPreferences(
				this).getString(SAVED_EDIT_TEXT, "");
		m_vwJokeEditText.setText(text);
		
		// Initialize the "Add Joke" listeners
		initAddJokeListeners();
	}

	/**
	 * Method used to encapsulate the code that initializes and sets the Layout
	 * for this Activity.
	 */
	protected void initLayout() {
		setContentView(R.layout.advanced);
		m_vwJokeLayout = (ListView) findViewById(R.id.jokeListViewGroup);
		m_vwJokeLayout.setChoiceMode(ListView.CHOICE_MODE_SINGLE);
		m_vwJokeEditText = (EditText) findViewById(R.id.newJokeEditText);
		m_vwJokeButton = (Button) findViewById(R.id.addJokeButton);
	}

	/**
	 * Method used to encapsulate the code that initializes and sets the Event
	 * Listeners which will respond to requests to "Add" a new Joke to the list.
	 */
	protected void initAddJokeListeners() {
		m_vwJokeButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View view) {
				String jokeText = m_vwJokeEditText.getText().toString(); 
				if (!jokeText.equals("")) {
					addJoke(new Joke(jokeText, m_strAuthorName));
					m_vwJokeEditText.setText("");
				}
			}
		});
		m_vwJokeEditText.setOnKeyListener(new OnKeyListener() {
			@Override
			public boolean onKey(View view, int keyCode, KeyEvent event) {
				String jokeText = m_vwJokeEditText.getText().toString();
				if (!jokeText.equals("") && event.getAction() == KeyEvent.ACTION_DOWN && 
				 (keyCode == KeyEvent.KEYCODE_DPAD_CENTER || keyCode == KeyEvent.KEYCODE_ENTER)) { 
					addJoke(new Joke(jokeText ,m_strAuthorName));
					m_vwJokeEditText.setText("");
					return true;
				}
				if (event.getAction() == KeyEvent.ACTION_UP && keyCode == KeyEvent.KEYCODE_DPAD_CENTER) {
					InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
					imm.hideSoftInputFromWindow(m_vwJokeEditText.getWindowToken(), 0);
					return true;
				}
				return false;
			}
		});
	}

	/**
	 * Method used for encapsulating the logic necessary to properly add a new
	 * Joke to m_arrJokeList, and display it on screen.
	 * 
	 * @param joke
	 *            The Joke to add to list of Jokes.
	 */
	protected void addJoke(Joke joke) {
		// Add joke
//		3.3.3 Maintaining the JokeList
		m_jokeDB.insertJoke(joke);
		m_arrJokeList.requery();
		
		m_jokeAdapter.notifyDataSetChanged();

		// Hide Soft Keyboard
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(m_vwJokeEditText.getWindowToken(), 0);
	}

	/**
	 * Method used to retrieve Jokes from online server. For the duration of
	 * this method a ProgressDialog will be displayed showing the default
	 * spinner animation.
	 */
	protected void getJokesFromServer() {
		try {
			URL url = new URL("http://simexusa.com/aac/getAllJokes.php");
			Scanner in = new Scanner(new InputStreamReader(url.openStream()))
					.useDelimiter("\n");
			while (in.hasNext()) {
				String joke = in.next();
				if (joke.length() != 0) {
					addJoke(new Joke(joke, m_strAuthorName));
				}
			}
		} catch (Exception e) {
		}
	}

	/**
	 * This method uploads a single Joke to the server. This method should test
	 * the response from the server and display success or failure to the user
	 * via a Toast Notification.
	 * 
	 * The addJoke script on the server requires two parameters, both of which
	 * should be encode in "UTF-8":
	 * 
	 * 1) "joke": The text of the joke.
	 * 
	 * 2) "author": The author of the joke.
	 * 
	 * @param joke
	 *            The Joke to be uploaded to the server.
	 * 
	 */
	protected void uploadJokeToServer(Joke joke) {
		try {
			URL url = new URL("http://simexusa.com/aac/addOneJoke.php?" + "joke="
					+ URLEncoder.encode(joke.getJoke(), "UTF-8") + "&author="
					+ URLEncoder.encode(joke.getAuthor(), "UTF-8"));

			Scanner in;
			in = new Scanner(url.openStream());

			String toastText = "Upload Succeeded!";
			if (!in.nextLine().equals("1 record added")) {
				toastText = "Upload failed. Sorry.";
			}
			Toast toast = Toast.makeText(this, toastText, Toast.LENGTH_SHORT);
			toast.show();
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View view, ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, view, menuInfo);

		MenuItem item = menu.add(Menu.NONE, REMOVE_JOKE_MENUITEM, Menu.NONE, R.string.remove_menuitem);
		item.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			@Override
			public boolean onMenuItemClick(MenuItem arg0) {
				long ID = m_jokeAdapter.getSelectedID();
				m_jokeDB.removeJoke(ID);
				m_arrJokeList.requery();
				m_jokeAdapter.notifyDataSetChanged();
				return true;
			}
		});

		item = menu.add(Menu.NONE, UPLOAD_JOKE_MENUITEM, Menu.NONE, R.string.upload_menuitem);
		item.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			@Override
			public boolean onMenuItemClick(MenuItem arg0) {
//				long ID = m_jokeAdapter.getSelectedID();
//				m_jokeDB.getJoke(ID);
//				m_arrJokeList.requery();
				uploadJokeToServer(m_jokeDB.getJoke(m_jokeAdapter
						.getSelectedID()));
				return true;
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		getMenuInflater().inflate(R.menu.menu, menu);
		menu.findItem(m_nFilter).setChecked(true);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int itemId = item.getItemId();
		switch (itemId) {
		case R.id.like_menuitem : 
		case R.id.dislike_menuitem :  
		case R.id.unrated_menuitem :  
		case R.id.show_all_menuitem :  
			setAndUpdateFilter(itemId);
			return true;
			
		case R.id.download_menuitem :
			getJokesFromServer();
			return true;
			
		default :
			return super.onOptionsItemSelected(item);
		}
	}
	
	/**
	 * This method sets m_nFilter to the ID of the currently selected Filter 
	 * MenuItem and updates the m_cursorJokeList to contain only Joke Database 
	 * Table rows with ratings matching the desired filter value. 
	 * 
	 * This method should stop managing and close any unused Cursor objects.
	 * Additionally it should start managing any new Cursor objects and update
	 * the JokeCursorAdapter with any new Cursor objects. 
	 * 
	 * @param newFilterID
	 * 			  The ID of the filter MenuItem used to determine which jokes
	 * 			  get displayed. This should be one of four filter MenuItem ID 
	 * 			  values: R.id.like_menuitem, R.id.dislike_menuitem, 
	 * 			  R.id.unrated_menuitem, or R.id.show_all_menuitem.  
	 */
	protected void setAndUpdateFilter(int newFilterID) {
		// TODO	
//		int filterVal = 0;
//		int ndx = 0;
//		Joke joke = null;
//		
//		// Set the filter value and Filter-SubMenu-Item checked
//		m_nFilter = newFilterID;
//		MenuItem filterItem = (MenuItem)findViewById(newFilterID);
//		if (filterItem != null) {
//			filterItem.setChecked(true);
//		}
//
//		// Set the filter value
//		switch (m_nFilter) {
//		case R.id.like_menuitem : 
//			filterVal = Joke.LIKE;
//			break;
//		case R.id.dislike_menuitem : 
//			filterVal = Joke.DISLIKE;
//			break;
//		case R.id.unrated_menuitem :  
//			filterVal = Joke.UNRATED;
//			break;
//		case R.id.show_all_menuitem :  
//		default :
//			filterVal = Joke.LIKE;
//			filterVal |= Joke.DISLIKE;
//			filterVal |= Joke.UNRATED;
//		}

//		3.3.2 Update Your Filtering Functionality
		stopManagingCursor(m_arrJokeList);
		m_arrJokeList.close();
		
		int filterVal = 0;
		m_nFilter = newFilterID;
		MenuItem filterItem = (MenuItem) findViewById(newFilterID);
		if (filterItem != null) {
			filterItem.setChecked(true);
		}
		// Set the filter value
		switch (m_nFilter) {
		case R.id.like_menuitem:
			filterVal = Joke.LIKE;
			m_arrJokeList = m_jokeDB.getAllJokes(Integer.toString(filterVal));
			break;
		case R.id.dislike_menuitem:
			filterVal = Joke.DISLIKE;
			m_arrJokeList = m_jokeDB.getAllJokes(Integer.toString(filterVal));
			break;
		case R.id.unrated_menuitem:
			filterVal = Joke.UNRATED;
			m_arrJokeList = m_jokeDB.getAllJokes(Integer.toString(filterVal));
			break;
		case R.id.show_all_menuitem:
			m_arrJokeList = m_jokeDB.getAllJokes(null);
		default:
			filterVal = Joke.LIKE;
			filterVal |= Joke.DISLIKE;
			filterVal |= Joke.UNRATED;
		}

		startManagingCursor(m_arrJokeList);
		m_jokeAdapter.changeCursor(m_arrJokeList);
		m_jokeAdapter.notifyDataSetChanged();
		
	}
	
//	2.1.1 Saving Instance Data.
	@Override
	public void onSaveInstanceState(Bundle outState){
	
		super.onSaveInstanceState(outState);
		outState.putInt(SAVED_FILTER_VALUE, m_nFilter);//?
	}
	
//	2.1.3 Restoring Instance Data.
	@Override
	public void onRestoreInstanceState(Bundle savedInstanceState){
		super.onRestoreInstanceState(savedInstanceState);
		if(savedInstanceState != null && savedInstanceState.containsKey(SAVED_FILTER_VALUE))
				m_nFilter = savedInstanceState.getInt(SAVED_FILTER_VALUE);
		setAndUpdateFilter(m_nFilter);
	}
	


//	2.2.1 Saving SharedPreference Data
	@Override
	public void onPause(){
		super.onPause();
		SharedPreferences.Editor mySPEditor = PreferenceManager
		.getDefaultSharedPreferences(this).edit();
		mySPEditor.putString(AdvancedJokeList.SAVED_EDIT_TEXT,m_vwJokeEditText.getText().toString());
		//Don't forget to commit your changes.
		mySPEditor.commit();
	}

@Override
public void onJokeChanged(JokeView view, Joke joke) {
	// TODO Auto-generated method stub
	 m_jokeDB.updateJoke(joke);
	 m_arrJokeList.requery();
	}
}