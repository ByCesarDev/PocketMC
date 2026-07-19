package com.mojang.minecraftpe;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Vibrator;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.text.format.DateFormat;
import android.widget.EditText;
import android.widget.FrameLayout;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.concurrent.CountDownLatch;

public class MainActivity extends Activity {

    private static final String TAG = "MCPE";

    static {
        System.loadLibrary("minecraftpe");
    }

    // Native methods
    private native void nativeRegisterThis();
    private native void nativeUnregisterThis();
    private native void nativeOnCreate(int screenWidth, int screenHeight);
    private native void nativeOnSurfaceCreated();
    private native void nativeOnSurfaceChanged(int w, int h);
    private native void nativeUpdate();
    private native void nativeOnDestroy();
    private native void nativeOnKeyDown(int keyCode);
    private native void nativeTextChar(int unicodeChar);
    private native void nativeOnKeyUp(int keyCode);
    private native boolean nativeHandleBack(boolean isDown);
    private native void nativeMouseDown(int pointerId, int buttonId, float x, float y);
    private native void nativeMouseUp(int pointerId, int buttonId, float x, float y);
    private native void nativeMouseMove(int pointerId, float x, float y);

    // Legacy JNI methods that the native side expects on this class
    public static void saveScreenshot(String filename, int width, int height, int[] pixels) {}
    public void postScreenshotToFacebook(String filename, int width, int height, int[] pixels) {}
    public int[] getImageData(String filename) {
        try {
            InputStream is = getAssets().open(filename);
            Bitmap bitmap = BitmapFactory.decodeStream(is);
            is.close();
            if (bitmap != null) {
                int w = bitmap.getWidth();
                int h = bitmap.getHeight();
                int[] pixels = new int[w * h + 2];
                pixels[0] = w;
                pixels[1] = h;
                bitmap.getPixels(pixels, 2, w, 0, 0, w, h);
                bitmap.recycle();
                return pixels;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public byte[] getFileDataBytes(String filename) {
        try {
            InputStream is = getAssets().open(filename);
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();
            int nRead;
            byte[] data = new byte[16384];
            while ((nRead = is.read(data, 0, data.length)) != -1) {
                buffer.write(data, 0, nRead);
            }
            is.close();
            return buffer.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
    public void playSound(String filename, float volume, float pitch) {}
    public void displayDialog(int dialogId) {}
    public void tick() {}
    public void quit() { finish(); }
    public void initiateUserInput(int id) {}
    public int getUserInputStatus() { return 0; }
    public String[] getUserInputString() { return new String[0]; }
    public String getDateString(int mode) {
        Calendar c = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US);
        return sdf.format(c.getTime());
    }
    public void vibrate(int ms) {
        Vibrator v = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        if (v != null) v.vibrate(ms);
    }
    public boolean supportsTouchscreen() {
        return getPackageManager().hasSystemFeature(PackageManager.FEATURE_TOUCHSCREEN);
    }
    public void setIsPowerVR(boolean is) {}
    public boolean isNetworkEnabled(boolean onlyWifi) {
        ConnectivityManager cm = (ConnectivityManager) getSystemService(CONNECTIVITY_SERVICE);
        if (cm == null) return false;
        NetworkInfo ni = cm.getActiveNetworkInfo();
        if (ni == null || !ni.isConnectedOrConnecting()) return false;
        if (onlyWifi) {
            return ni.getType() == ConnectivityManager.TYPE_WIFI;
        }
        return true;
    }
    public float getPixelsPerMillimeter() {
        DisplayMetrics dm = getResources().getDisplayMetrics();
        float xDpi = dm.xdpi;
        return xDpi / 25.4f;
    }
    public String getPlatformStringVar(int id) {
        switch (id) {
            case 0:
                try {
                    PackageInfo pi = getPackageManager().getPackageInfo(getPackageName(), 0);
                    return pi.versionName;
                } catch (Exception e) {
                    return "unknown";
                }
            default:
                return "";
        }
    }
    public void openURL(String url) {
        try {
            Intent i = new Intent(Intent.ACTION_VIEW, android.net.Uri.parse(url));
            startActivity(i);
        } catch (Exception e) {}
    }
    public int getScreenWidth() {
        DisplayMetrics dm = getResources().getDisplayMetrics();
        return dm.widthPixels;
    }
    public int getScreenHeight() {
        DisplayMetrics dm = getResources().getDisplayMetrics();
        return dm.heightPixels;
    }
    public int getKeyFromKeyCode(int keyCode, int metaState, int deviceId) {
        return 0;
    }
    protected boolean isDemo() { return false; }
    public void buyGame() {}

    // Fields
    private GLSurfaceView glSurfaceView;
    private FrameLayout container;
    private EditText hiddenEdit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        nativeRegisterThis();

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN
        );
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.main);

        container = (FrameLayout) findViewById(R.id.container);

        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(1);
        glSurfaceView.setRenderer(new GLRenderer(this));
        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        glSurfaceView.setZOrderMediaOverlay(false);
        glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                return MainActivity.this.handleTouch(event);
            }
        });

        container.addView(glSurfaceView, 0);

        // Hidden EditText for soft keyboard text input
        hiddenEdit = new EditText(this);
        hiddenEdit.setAlpha(0);
        hiddenEdit.setWidth(1);
        hiddenEdit.setHeight(1);
        hiddenEdit.setInputType(android.text.InputType.TYPE_CLASS_TEXT);
        hiddenEdit.setFilters(new InputFilter[]{ new InputFilter.LengthFilter(1) });
        hiddenEdit.addTextChangedListener(new TextWatcher() {
            @Override public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {
                if (s.length() > 0) {
                    char c = s.charAt(0);
                    nativeTextChar((int) c);
                    s.clear();
                }
            }
        });
        FrameLayout.LayoutParams editParams = new FrameLayout.LayoutParams(1, 1);
        container.addView(hiddenEdit, editParams);

        DisplayMetrics dm = getResources().getDisplayMetrics();
        int screenW = dm.widthPixels;
        int screenH = dm.heightPixels;

        nativeOnCreate(screenW, screenH);
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onStop() {
        nativeUnregisterThis();
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        nativeOnDestroy();
        super.onDestroy();
    }

    private boolean handleTouch(MotionEvent event) {
        int action = event.getActionMasked();
        int pointerIndex = event.getActionIndex();
        int pointerId = event.getPointerId(pointerIndex);
        float x = event.getX(pointerIndex);
        float y = event.getY(pointerIndex);

        switch (action) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
                nativeMouseDown(pointerId, 0, x, y);
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
            case MotionEvent.ACTION_CANCEL:
                nativeMouseUp(pointerId, 0, x, y);
                break;
            case MotionEvent.ACTION_MOVE:
                // Forward all active pointers on MOVE
                for (int i = 0; i < event.getPointerCount(); i++) {
                    nativeMouseMove(event.getPointerId(i), event.getX(i), event.getY(i));
                }
                break;
        }
        return true;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        nativeOnKeyDown(keyCode);
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        nativeOnKeyUp(keyCode);
        return super.onKeyUp(keyCode, event);
    }

    @Override
    public void onBackPressed() {
        if (!nativeHandleBack(true)) {
            super.onBackPressed();
        }
    }

    public void showSoftKeyboard() {
        if (hiddenEdit != null) {
            hiddenEdit.requestFocus();
            InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
            if (imm != null) {
                imm.showSoftInput(hiddenEdit, InputMethodManager.SHOW_IMPLICIT);
            }
        }
    }

    public void hideSoftKeyboard() {
        if (hiddenEdit != null) {
            InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
            if (imm != null) {
                imm.hideSoftInputFromWindow(hiddenEdit.getWindowToken(), 0);
            }
        }
    }

    public GLSurfaceView getGLSurfaceView() {
        return glSurfaceView;
    }
}
