package com.example.sunkai.service;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Binder;
import android.os.IBinder;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

public class MyService extends Service {
    private static final String TAG = "MyService";
    private DownloadBinder mBinder=new DownloadBinder();
    public class DownloadBinder extends Binder {
        public void startDownload(){
            Log.d(TAG, "startDownload: executed");
        }
        public int getProgress(){
            Log.d(TAG, "getProgress: getProgress executed");
            return 0;
        }
    }
    public MyService() {
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(TAG, "onCreate");
        //创建一个前台服务
        Intent intent=new Intent(this,MainActivity.class);
        PendingIntent pendingIntent=PendingIntent.getActivity(this,0,intent,0);
        Notification notification=new NotificationCompat.Builder(this,"2").setContentTitle("this is content title")
                .setContentText("this is content text")
                .setWhen(System.currentTimeMillis())
                .setSmallIcon(R.drawable.ic_launcher_foreground)
                .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher_foreground))
                .setContentIntent(pendingIntent)
                .build();
        startForeground(1,notification);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        //服务一起动就执行某些方法
        Log.d(TAG, "onStartCommand");
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy");
    }
}
