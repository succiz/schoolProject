/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package edu.calpoly.android.walkabout;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.Bitmap.CompressFormat;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.OrientationEventListener;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Toast;

// ----------------------------------------------------------------------

public class CameraPreview extends Activity implements PictureCallback {    
    private Preview mPreview;
    
	public static final String IMAGE_FILE_NAME = "IMAGE_FILE_NAME";
    
    @Override
	protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Hide the window title.
        requestWindowFeature(Window.FEATURE_NO_TITLE);
    
        // Create our Preview view and set it as the content of our activity.
        mPreview = new Preview(this);
        setContentView(mPreview);
        
        mPreview.setOnClickListener(new OnClickListener(){
        	public void onClick(View view){
        		mPreview.getCamera().takePicture(null, null,CameraPreview.this);
        		Toast.makeText(getApplicationContext(),R.string.takePicture,
						Toast.LENGTH_SHORT).show();
        	}
        });
    }

	@Override
	public void onPictureTaken(byte[] data, Camera camera) {
    	// TODO
		File myFile = new File
						(Environment.getExternalStorageDirectory(),
								(System.currentTimeMillis()+ ".jpg"));
		
		try {
			FileOutputStream outStream = new FileOutputStream(myFile);
			outStream.write(data);
			outStream.flush();
			outStream.close();
			
			Intent intent = new Intent();
			String uri = myFile.getAbsolutePath();
			intent.putExtra(CameraPreview.IMAGE_FILE_NAME,uri);
//			Log.i("lab5","file:"+intent.getExtras().getString(CameraPreview.IMAGE_FILE_NAME));
			setResult(RESULT_OK, intent);
			finish();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			setResult(RESULT_CANCELED,null);
			finish();
		}
		//?????????????????????????????????????????????
	}
}

// ----------------------------------------------------------------------

//----------------------------------------------------------------------

class Preview extends SurfaceView implements SurfaceHolder.Callback {
    SurfaceHolder mHolder;
    Camera mCamera;
    
    Preview(Context context) {
        super(context);
        
        // Install a SurfaceHolder.Callback so we get notified when the
        // underlying surface is created and destroyed.
        mHolder = getHolder();
        mHolder.addCallback(this);
        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    public void surfaceCreated(SurfaceHolder holder) {
        // The Surface has been created, acquire the camera and tell it where
        // to draw.
        mCamera = Camera.open();
        try {
           mCamera.setPreviewDisplay(holder);
        } catch (IOException exception) {
            mCamera.release();
            mCamera = null;
        }
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        // Surface will be destroyed when we return, so stop the preview.
        // Because the CameraDevice object is not a shared resource, it's very
        // important to release it when the activity is paused.
        mCamera.stopPreview();
        mCamera.release();
        mCamera = null;
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        // Now that the size is known, set up the camera parameters and begin
        // the preview.
        Camera.Parameters parameters = mCamera.getParameters();
//        parameters.setPreviewSize(w, h);
       Log.i("lab5","w:"+w+"h:"+h+"param"+parameters.toString());
        mCamera.setParameters(parameters);
       
        mCamera.startPreview();
    }
    
    public Camera getCamera() {
    	return mCamera;
    }
}
