package com.example.user.broadcast;

import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    IntentFilter filter;
    AlarmReceiver receiver;
    Button button,button2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=(Button)findViewById(R.id.button);
        button2=(Button)findViewById(R.id.button2);

        button.setOnClickListener((view)->{
            Intent intent=new Intent("android.intent.action.ALARM_RECEIVER");

            //Android 8.0当中采用了更加严格的广播限制
            //静态注册的广播（比如本程序的ALARM_RECIEVER）将不能收到隐式广播
            //需要显示发送广播，即发送packageName和className
            if(Build.VERSION.SDK_INT>=26)
                intent.setClassName("com.example.user.broadcast","com.example.user.broadcast.AlarmReceiver");
            sendBroadcast(intent);
        });

        //一个动态申请的广播
        //可以用原来的方法发送
        button2.setOnClickListener((view)->{
            Intent intent=new Intent("action");
            sendBroadcast(intent);
        });
    }

    //动态申请广播
    @Override
    protected void onStart() {
        super.onStart();
        filter=new IntentFilter("action");
        receiver=new AlarmReceiver();
        registerReceiver(receiver,filter);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(receiver);
    }
}
