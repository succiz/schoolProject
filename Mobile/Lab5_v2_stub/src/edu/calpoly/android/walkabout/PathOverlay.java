package edu.calpoly.android.walkabout;

import java.util.List;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.RectF;
import android.util.Log;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapView;
import com.google.android.maps.Overlay;
import com.google.android.maps.Projection;

public class PathOverlay extends Overlay {

	private final List<GeoPoint> m_arrPathPoints;

	private Point m_point;
	private Point m_point2;
	private Paint m_paint;
	private RectF m_rect;

	private static final int START_RADIUS = 10;
	private static final int PATH_WIDTH = 6;

	public PathOverlay(List<GeoPoint> pathPoints) {
		super();
		// TODO
		m_arrPathPoints = pathPoints;
		m_point = new Point();
		m_point2 = new Point();
		m_paint = new Paint();
		m_rect = new RectF();
	}

	@Override
	public void draw(Canvas canvas, MapView mapView, boolean shadow) {
		// TODO
		if (m_arrPathPoints.size() == 0)
			return;
		m_paint.setARGB(255, 0, 255, 0);
		Projection projection = mapView.getProjection();
//		Log.i("lab5", "2");
		projection.toPixels(m_arrPathPoints.get(0), m_point);// ??????????
//		Log.i("lab5", "3");
		m_rect.set(m_point.x - START_RADIUS, m_point.y - START_RADIUS,
				m_point.x + START_RADIUS, m_point.y + START_RADIUS);
		canvas.drawOval(m_rect, m_paint);
//		Log.i("lab5", "5");
		
		
		m_paint.setARGB(255, 255, 0, 0);
		for (int i = 1; i < m_arrPathPoints.size(); i++) {
			projection.toPixels(m_arrPathPoints.get(i), m_point2);
			m_paint.setStrokeWidth(PathOverlay.PATH_WIDTH);
			canvas.drawLine(m_point.x, m_point.y, m_point2.x, m_point2.y,
					m_paint);
			m_point.set(m_point2.x, m_point2.y);
//			Log.i("lab5","6");
		}
	}
}
