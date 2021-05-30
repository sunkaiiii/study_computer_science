package com.example.sunkai.a0604test;

import android.animation.ValueAnimator;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v4.widget.ViewDragHelper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.ImageView;

public class Main2Activity extends AppCompatActivity {

    private int mLastX=0;
    private int mLastY=0;
    private Button button;
    private Button button2;

    final int startX=0;
    final int deltaX=100;

    private final int MESSAGE_SCROLL_TO=1;
    private final int FRAME_COUNT=30;
    private final int DELAYED_TIME=33;

    private int mCount=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        button=findViewById(R.id.button2);
        button2=findViewById(R.id.button3);

        button.setOnClickListener((v)->{
            ValueAnimator animator=ValueAnimator.ofInt(0,1).setDuration(1000);
            animator.addUpdateListener(animation -> {
                float fraction=animation.getAnimatedFraction();
                button.scrollTo(startX+(int)(deltaX*fraction),0);
            });
            animator.start();
        });
        button2.setOnClickListener((v)->{
            mHandler.sendEmptyMessage(MESSAGE_SCROLL_TO);
        });
    }

    private Handler mHandler=new Handler(Looper.getMainLooper()){
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what){
                case MESSAGE_SCROLL_TO:{
                    mCount++;
                    if(mCount<=FRAME_COUNT){
                        float fraction=mCount/(float)FRAME_COUNT;
                        int scrollX=(int)(fraction*100);
                        button2.scrollTo(scrollX,0);
                        mHandler.sendEmptyMessageDelayed(MESSAGE_SCROLL_TO,DELAYED_TIME);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int x=(int)event.getRawX();
        int y=(int)event.getRawY();
        switch (event.getAction()){
            case MotionEvent.ACTION_DOWN:
                break;
            case MotionEvent.ACTION_MOVE:
                int deltaX=x-mLastX;
                int deltaY=y-mLastY;
                Log.d("test4","move , deltaX:"+deltaX+" deltaY:"+deltaY);
                int translationX=(int) getWindow().getDecorView().getTranslationX()+deltaX;
                int translationY=(int)getWindow().getDecorView().getTranslationY()+deltaY;
                getWindow().getDecorView().setTranslationX(translationX);
                getWindow().getDecorView().setTranslationY(translationY);
                break;
            case MotionEvent.ACTION_UP:
                break;
                default:
                    break;
        }
        mLastX=x;
        mLastY=y;
        return true;
    }
}
