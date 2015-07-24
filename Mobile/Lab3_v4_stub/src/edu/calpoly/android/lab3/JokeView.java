package edu.calpoly.android.lab3;

import android.content.Context;
import android.text.TextUtils.TruncateAt;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
//import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
//import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.Checkable;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class JokeView extends LinearLayout implements OnClickListener,
		RadioGroup.OnCheckedChangeListener, Checkable {

	private Button m_vwExpandButton;
	private RadioButton m_vwLikeButton;
	private RadioButton m_vwDislikeButton;
	private RadioGroup m_vwLikeGroup;
	private TextView m_vwJokeText;
	private Joke m_joke;
	private Context m_context;

	public static final String EXPAND = " + ";
	public static final String COLLAPSE = " - ";

	/**
	 * Basic Constructor that takes only takes in an application Context.
	 * 
	 * @param context
	 *            The application Context in which this view is being added.
	 * 
	 * @param joke
	 *            The Joke this view is responsible for displaying.
	 */
	public JokeView(Context context, Joke joke) {
		super(context);
		m_context = context;
		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		inflater.inflate(R.layout.joke_view, this, true);

		m_vwLikeButton = (RadioButton) findViewById(R.id.likeButton);
		m_vwDislikeButton = (RadioButton) findViewById(R.id.dislikeButton);

		m_vwLikeGroup = (RadioGroup) findViewById(R.id.ratingRadioGroup);
		m_vwLikeGroup.setOnCheckedChangeListener(this);

		m_vwJokeText = (TextView) findViewById(R.id.jokeTextView);
		m_vwExpandButton = (Button) findViewById(R.id.expandButton);
		m_vwExpandButton.setOnClickListener(this);

		setJoke(joke);
		collapseJokeView();
	}

	/**
	 * Mutator method for changing the Joke object this View displays. This View
	 * will be updated to display the correct contents of the new Joke.
	 * 
	 * @param joke
	 *            The Joke object which this View will display.
	 */
	public void setJoke(Joke joke) {
		m_joke = joke;
		m_vwJokeText.setText(joke.getJoke());// ?
		if (joke.getRating() == Joke.LIKE) {
			m_vwLikeButton.setChecked(true);
		} else if (joke.getRating() == Joke.DISLIKE) {
			m_vwDislikeButton.setChecked(true);
		} else {
			m_vwLikeGroup.clearCheck();
		}

	}

	/**
	 * This method encapsulates the logic necessary to update this view so that
	 * it displays itself in its "Expanded" form: - Shows the complete text of
	 * the joke. - Brings the RadioGroup of rating Buttons back into view.
	 */
	private void expandJokeView() {
		m_vwJokeText.setEllipsize(null);// ?
		m_vwExpandButton.setText(JokeView.COLLAPSE);
		m_vwLikeGroup.setVisibility(VISIBLE);
		requestLayout();
	}

	/**
	 * This method encapsulates the logic necessary to update this view so that
	 * it displays itself in its "Collapsed" form: - Shows only the first line
	 * of text of the joke. - If the joke is longer than one line, it appends an
	 * ellipsis to the end. - Removes the RadioGroup of rating Buttons from
	 * view.
	 */
	private void collapseJokeView() {
		//m_vwJokeText = new EditText(m_context);
		m_vwJokeText.setEllipsize(TruncateAt.END);

		m_vwExpandButton.setText(JokeView.EXPAND);
		m_vwLikeGroup.setVisibility(GONE);
		requestLayout();
	}

	@Override
	public void onClick(View v) {
		if (m_vwExpandButton.getText().toString() == EXPAND)
			collapseJokeView();
		if (m_vwExpandButton.getText().toString() == COLLAPSE)
			expandJokeView();
	}

	@Override
	public void onCheckedChanged(RadioGroup group, int checkedId) {
		// m_vwLikeGroup
		if (checkedId == R.id.likeButton) {
			m_joke.setRating(Joke.LIKE);
		} else if (checkedId == R.id.dislikeButton) {
			m_joke.setRating(Joke.DISLIKE);
		} else if (checkedId == -1) {
			m_joke.setRating(Joke.UNRATED);
		}

	}

	// @Override
	public boolean isChecked() {
		if (m_vwExpandButton.getText().toString() == EXPAND) {
			return false;
		} else {
			return true;
		}
	}

	// @Override
	public void setChecked(boolean checked) {
		if (checked) {
			expandJokeView();
		} else {
			collapseJokeView();
		}
	}

	// @Override
	public void toggle() {
		setChecked(!isChecked());
	}

}
