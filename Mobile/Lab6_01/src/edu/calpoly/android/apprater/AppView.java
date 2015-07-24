package edu.calpoly.android.apprater;

import android.content.Context;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;

public class AppView extends LinearLayout {

	private App m_app;

	public AppView(Context context, App app) {
		super(context);

		((LayoutInflater)context
		 .getSystemService(Context.LAYOUT_INFLATER_SERVICE))
		 .inflate(R.layout.app_view, this, true);
		
		m_app = app;
		initLayout();
	}
		
	private void initLayout() {
		TextView appName = (TextView)findViewById(R.id.appName);
		appName.setText(m_app.getName());
		
		if (!m_app.isInstalled()) {
			appName.setBackgroundColor(getContext().getResources().getColor(R.color.new_app));
		}
		else if (m_app.getRating() == App.UNRATED) {
			appName.setBackgroundColor(getContext().getResources().getColor(R.color.installed_app));
		}
		else {
			appName.setBackgroundColor(getContext().getResources().getColor(R.color.rated_app));
		}
	}
	
	public App getApp() {
		return m_app;
	}
	
	public void setApp(App app) {
		m_app = app;
		initLayout();
		postInvalidate();
	}
}