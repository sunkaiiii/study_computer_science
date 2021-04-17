package com.example.user.onkeylongpress;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private boolean shortPress=false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onKeyLongPress(int keyCode, KeyEvent event) {
        if(keyCode==KeyEvent.KEYCODE_VOLUME_DOWN){
            shortPress=false;
            Toast.makeText(this,"longPress",Toast.LENGTH_LONG).show();
            return true;
        }
        return false;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if(keyCode==KeyEvent.KEYCODE_VOLUME_DOWN){
            if(event.getAction()==KeyEvent.ACTION_DOWN){
                event.startTracking();
                if(event.getRepeatCount()==0){
                    shortPress=true;
                }
                return true;
            }
        }
        return super.onKeyDown(keyCode,event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        if(keyCode==KeyEvent.KEYCODE_VOLUME_DOWN){
            if(shortPress){
                Toast.makeText(this,"shortPress",Toast.LENGTH_LONG).show();
            }
            shortPress=false;
            return true;
        }
        return super.onKeyUp(keyCode,event);
    }
}
