package com.example.sunkai.a0604test;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.VelocityTracker;
import android.view.View;
import android.view.ViewConfiguration;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements GestureDetector.OnGestureListener{

    GestureDetector mGestureDetector;
    TextView textView;
    Button button,button2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d("test", String.valueOf(ViewConfiguration.get(this).getScaledTouchSlop()));
        mGestureDetector=new GestureDetector(this,this);
        mGestureDetector.setIsLongpressEnabled(false);
        textView=findViewById(R.id.textview);
        button=findViewById(R.id.button);
        button2=findViewById(R.id.button2);
        textView.setOnClickListener(v -> v.scrollBy(-20,-20));
        button.setOnClickListener(v -> startActivity(new Intent(MainActivity.this,Main2Activity.class)));
        button2.setOnClickListener((v)-> startActivity(new Intent(MainActivity.this,Main3Activity.class)));
        findViewById(R.id.remoteview).setOnClickListener((v)->{
            startActivity(new Intent(this,Main4Activity.class));
        });
        findViewById(R.id.button4).setOnClickListener((v)->startActivity(new Intent(MainActivity.this,Main5Activity.class)));
        findViewById(R.id.button5).setOnClickListener((v)->startActivity(new Intent(MainActivity.this,Main6Activity.class)));
    }

    //滑动速度追踪
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        VelocityTracker velocityTracker=VelocityTracker.obtain();
        velocityTracker.addMovement(event);
        velocityTracker.computeCurrentVelocity(1000);
        int x=(int)velocityTracker.getXVelocity();
        int y=(int)velocityTracker.getYVelocity();
        Log.d("test2",String.valueOf(x)+","+String.valueOf(y));
        velocityTracker.clear();
        velocityTracker.recycle();
        return mGestureDetector.onTouchEvent(event);
    }

    @Override
    public boolean onDown(MotionEvent e) {
        Log.d("test3","onDown");
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {
        Log.d("test3","onShowPress");
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        Log.d("test3","onSingleTapUp");
        return false;
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        Log.d("test3","onScroll");
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {
        Log.d("test3","onLongPress");
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        Log.d("test3","onFling");
        return false;
    }
}
