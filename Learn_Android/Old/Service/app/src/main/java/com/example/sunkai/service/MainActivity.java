package com.example.sunkai.service;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private Button button,button2,button3,button4;
    private MyService.DownloadBinder downloadBinder;

    private ServiceConnection connection=new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            downloadBinder=(MyService.DownloadBinder)iBinder;
            downloadBinder.startDownload();
            downloadBinder.getProgress();
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=findViewById(R.id.button);
        button2=findViewById(R.id.button2);
        button3=findViewById(R.id.button3);
        button4=findViewById(R.id.button4);

        button.setOnClickListener(this);
        button2.setOnClickListener(this);
        button3.setOnClickListener(this);
        button4.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.button:
                Intent startIntent=new Intent(this,MyService.class);
                startService(startIntent);
                break;
            case R.id.button2:
                Intent stopIntent=new Intent(this,MyService.class);
                stopService(stopIntent);
                break;
            case R.id.button3:
                Intent bindIntent=new Intent(this,MyService.class);
                bindService(bindIntent,connection,BIND_AUTO_CREATE); //绑定服务
                break;
            case R.id.button4:
                unbindService(connection);
            default:
                break;
        }
    }
}
