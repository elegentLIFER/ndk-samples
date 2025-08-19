package com.example.hellolibs;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
/*
 * Simple Java UI to trigger jni function. It is exactly same as Java code
 * in hello-jni.
 */
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TextView tv = new TextView(this);
        tv.setText( "The calculation took " + measureTicks() + " ticks" );
        setContentView(tv);
    }
    public native long  measureTicks();
    static {
        System.loadLibrary("hello-libs");
    }

}
