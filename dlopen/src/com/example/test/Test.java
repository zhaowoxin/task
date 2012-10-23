package com.example.test;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import java.lang.String;



public class Test extends Activity {

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
  
        TextView tv = new TextView(this);
  
        System.loadLibrary("test");

  
        tv.setText("result =" + test()); 
        
        setContentView(tv);
    }

    public native int test();
}
