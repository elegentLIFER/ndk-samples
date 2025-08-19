package com.android.gles3jni;

// Wrapper for native library

public class GLES3JNILib {

     static {
          System.loadLibrary("gles3jni");
     }

     public static native void init();
     public static native void resize(int width, int height);
     public static native void step();
}
