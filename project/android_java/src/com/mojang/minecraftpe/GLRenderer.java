package com.mojang.minecraftpe;

import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {

    private native static void nativeOnSurfaceCreated();
    private native static void nativeOnSurfaceChanged(int w, int h);
    private native static void nativeUpdate();

    private final MainActivity activity;

    public GLRenderer(MainActivity activity) {
        this.activity = activity;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeOnSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeUpdate();
    }
}
