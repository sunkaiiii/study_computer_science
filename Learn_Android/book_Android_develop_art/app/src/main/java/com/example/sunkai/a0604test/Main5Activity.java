package com.example.sunkai.a0604test;

import android.graphics.PixelFormat;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.Button;

public class Main5Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main5);
    }

    @Override
    public void onAttachedToWindow() {
        super.onAttachedToWindow();
        //闪退，运行不能
        Button button=new Button(this);
        button.setText("windowButton");
        WindowManager.LayoutParams layoutParams=new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT,0,0, PixelFormat.TRANSPARENT
        );
        layoutParams.flags= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL
                | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                | WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED;
        layoutParams.gravity= Gravity.LEFT|Gravity.TOP;
        layoutParams.x=100;
        layoutParams.y=300;
        getWindowManager().addView(button,layoutParams);
    }
    private Handler handler=new Handler(getMainLooper()){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
        }
    };
}
