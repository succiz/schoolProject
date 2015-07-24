package edu.calpoly.android.lab3;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Scanner;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

public class AdvancedJokeList extends Activity {

	/**
	 * Contains the name of the Author for the jokes.
	 */
	protected String m_strAuthorName;

	/**
	 * Contains the list of Jokes the Activity will present to the user.
	 **/
	protected ArrayList<Joke> m_arrJokeList;

	/**
	 * Adapter used to bind an AdapterView to List of Jokes.
	 */
	protected JokeListAdapter m_jokeAdapter;

	/**
	 * ViewGroup used for maintaining a list of Views that each display Jokes.
	 **/
	protected ListView m_vwJokeLayout;

	/**
	 * EditText used for entering text for a new Joke to be added to
	 * m_arrJokeList.
	 **/
	protected EditText m_vwJokeEditText;

	/**
	 * Button used for creating and adding a new Joke to m_arrJokeList using the
	 * text entered in m_vwJokeEditText.
	 **/
	protected Button m_vwJokeButton;

	/**
	 * Context-Menu MenuItem ID's IMPORTANT: You must use these when creating
	 * your MenuItems or the tests used to grade your submission will fail.
	 */
	protected static final int REMOVE_JOKE_MENUITEM = Menu.FIRST;
	protected static final int UPLOAD_JOKE_MENUITEM = Menu.FIRST + 1;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Initialize the ContentView
		initLayout();

		Resources myResources = this.getResources();
		m_strAuthorName = myResources.getString(R.string.author_name);

		m_arrJokeList = new ArrayList<Joke>();
		m_jokeAdapter = new JokeListAdapter(this, m_arrJokeList);
		
		m_vwJokeLayout.setChoiceMode(1);
		m_vwJokeLayout.setAdapter(m_jokeAdapter);
		m_vwJokeLayout.setOnItemLongClickListener(m_jokeAdapter);
		registerForContextMenu(m_vwJokeLayout);

		String[] resJokes = myResources.getStringArray(R.array.jokeList);
		for (int ndx = 0; ndx < resJokes.length; ndx++) {
			addJoke(new Joke(resJokes[ndx], m_strAuthorName));
		}
		
		initAddJokeListeners();
	}

	/**
	 * Method is used to encapsulate the code that initializes and sets the
	 * Layout for this Activity.
	 */
	protected void initLayout() {
		this.setContentView(R.layout.advanced);
		m_vwJokeEditText = (EditText) findViewById(R.id.newJokeEditText);
		m_vwJokeButton = (Button) findViewById(R.id.addJokeButton);

		m_vwJokeLayout = (ListView) findViewById(R.id.jokeListViewGroup);
	}

	/**
	 * Method is used to encapsulate the code that initializes and sets the
	 * Event Listeners which will respond to requests to "Add" a new Joke to the
	 * list.
	 */
	protected void initAddJokeListeners() {
		m_vwJokeButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View view) {

				// Implement code to add a new joke here...
				Joke myJoke = new Joke();
				myJoke.setJoke(m_vwJokeEditText.getText().toString());
				if (!m_vwJokeEditText.equals(""))
					addJoke(myJoke);
				m_vwJokeEditText.setText("");
			}
		});
		m_vwJokeEditText.setOnKeyListener(new OnKeyListener() {
			@Override
			public boolean onKey(View view, int keyCode, KeyEvent event) {
				String jokeText = m_vwJokeEditText.getText().toString();
				if (!jokeText.equals("")
						&& event.getAction() == KeyEvent.ACTION_DOWN
						&& (keyCode == KeyEvent.KEYCODE_DPAD_CENTER || keyCode == KeyEvent.KEYCODE_ENTER)) {
					addJoke(new Joke(jokeText, m_strAuthorName));
					m_vwJokeEditText.setText("");
					return true;
				}
				if (event.getAction() == KeyEvent.ACTION_UP
						&& keyCode == KeyEvent.KEYCODE_DPAD_CENTER) {
					InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
					imm.hideSoftInputFromWindow(
							m_vwJokeEditText.getWindowToken(), 0);
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
		// Add Joke
		m_arrJokeList.add(joke);
		m_jokeAdapter.notifyDataSetChanged();
		// Hide Soft Keyboard
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(m_vwJokeEditText.getWindowToken(), 0);
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
			ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, v, menuInfo);
		MenuItem m_menuItem = menu.add(Menu.NONE,
				AdvancedJokeList.REMOVE_JOKE_MENUITEM, Menu.NONE,
				R.string.remove_menuitem);
		m_menuItem.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			@Override
			public boolean onMenuItemClick(MenuItem arg0) {
				m_arrJokeList.remove(m_jokeAdapter.getSelectedPosition());// ?adapter
																			// get
																			// a
																			// joke?
				m_jokeAdapter.notifyDataSetChanged();
				return true;
			}
		});
		MenuItem m_menuItem2 = menu.add(Menu.NONE,
				AdvancedJokeList.UPLOAD_JOKE_MENUITEM, Menu.NONE,
				R.string.remove_menuitem);
		m_menuItem2.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			@Override
			public boolean onMenuItemClick(MenuItem arg0) {
				uploadJokeToServer(m_arrJokeList.get(m_jokeAdapter
						.getSelectedPosition()));
				return true;
			}
		});

	}

	/**
	 * Method used to retrieve Jokes from online server. The getJoke script
	 * takes a single optional parameter, which should be encode in "UTF-8".
	 * This parameter allows tells script to only retrieve Jokes whose author
	 * name matches the value in the parameter.
	 * 
	 * param-1) "author": The author of the joke.
	 * 
	 * URL: http://simexusa.com/aac/getJokes.php?
	 * 
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
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * This method uploads a single Joke to the server. This method should test
	 * the response from the server and display success or failure to the user
	 * via a Toast Notification
	 * 
	 * The addJoke script on the server requires two parameters, both of which
	 * should be encode in "UTF-8":
	 * 
	 * param-1) "joke": The text of the joke.
	 * 
	 * param-2) "author": The author of the joke.
	 * 
	 * URL: http://simexusa.com/aac/addJoke.php?
	 * 
	 * @param joke
	 *            The Joke to be uploaded to the server.
	 * 
	 */
	protected void uploadJokeToServer(Joke joke) {
		try {
			String urlString = "http://simexusa.com/aac/addOneJoke.php?"
					+ "joke=" + URLEncoder.encode(joke.getJoke(), "UTF-8")
					+ "&author=" + URLEncoder.encode(joke.getAuthor(), "UTF-8");
			URL url = new URL(urlString);
			Scanner in;
			in = new Scanner(url.openStream());

			String toastText = "Upload Succeeded!";
			if (!in.nextLine().equals("1 record added")) {
				toastText = "Upload failed. Sorry.";
			}
			Toast toast = Toast.makeText(this, toastText, Toast.LENGTH_SHORT);
			toast.show();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}