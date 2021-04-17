package com.example.user.testproject;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationManagerCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;

import java.io.InputStream;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private Button btnTest,btnCancel,btnCancelOne,btnProgress;
    EditText idEditText;
    NotificationManager notificationManager;
    int count=0;
    private static final String TAG="MainActivity";
    private void init(){
        btnTest = (Button) findViewById(R.id.btn_test_btn);
        btnCancel=(Button)findViewById(R.id.btn_cancel);
        btnCancelOne=(Button)findViewById(R.id.btn_cancel_one);
        idEditText=(EditText)findViewById(R.id.editText_id);
        btnProgress=(Button)findViewById(R.id.btn_progress);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        init();
        btnTest.setOnClickListener((view) -> {
            Random random=new Random();
            count++;
            sendNotification(count,"message Test");
        });


        btnCancel.setOnClickListener((view -> {
            cancelNotification();
        }));

        btnCancelOne.setOnClickListener((view -> {
            int id=Integer.parseInt(idEditText.getText().toString());
            cancelNotification(id);
        }));

        btnProgress.setOnClickListener((view -> {
            showProgressNotification();
        }));
    }

    private void cancelNotification(int id){
        notificationManager.cancel(id);
    }
    private void cancelNotification(){
        if(notificationManager!=null){
            notificationManager.cancelAll();
        }
    }
    private void showProgressNotification(){
        notificationManager=(NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        NotificationCompat.Builder builder=new NotificationCompat.Builder(this,"progress");
        builder.setContentTitle("Download")
                .setContentText("download in progress")
                .setSmallIcon(R.drawable.choclate);
        //启动一个虚假的下载线程
        new Thread(()->{
            int incr;

            for(incr=0;incr<=100;incr+=5){
                builder.setProgress(100,incr,false);
                notificationManager.notify(1,builder.build());
                try{
                    Thread.sleep(1*100);
                }catch (InterruptedException e){
                    Log.d(TAG,"sleep error");
                }
            }
            //循环完成，更新notification，然后销毁
            builder.setContentText("Download complete").setProgress(0,0,false);

            //设置优先级并使用响铃和震动，用于触发Android 5.1以上的浮动通知
            builder.setPriority(NotificationCompat.PRIORITY_MAX).setDefaults(NotificationCompat.DEFAULT_ALL);
            notificationManager.notify(1,builder.build());
        }).start();

    }
    private void sendNotification(int id,String content) {
        Intent mainIntent = new Intent(this, MainActivity.class);

        //pendingIntent用于在某个事件结束后执行的特定的Action
        //在这里应用为用户点击通知，才会执行
        PendingIntent mainPendingIntent=PendingIntent.getActivity(this,1,mainIntent,PendingIntent.FLAG_UPDATE_CURRENT);
        Resources res=getResources();
        Bitmap bit=BitmapFactory.decodeResource(res,R.drawable.choclate);
        notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if(Build.VERSION.SDK_INT>=26) {
            //安卓8.0推送的方式有所改变
            //要向某个应用的通知channel发送通知
            //所以首先创建一个channel
            NotificationChannel channel=new NotificationChannel("1","Channel",NotificationManager.IMPORTANCE_DEFAULT);
            //使用此channel的时候使用的各项通知数据
            channel.enableLights(true);
            channel.setLightColor(Color.GREEN);
            channel.setShowBadge(true);
            //创建channel
            notificationManager.createNotificationChannel(channel);
            //绑定对应的channel id
            Notification.Builder builder=new Notification.Builder(this,"1");
            builder.setContentTitle(content)
                    .setContentText(content)
                    .setSmallIcon(R.drawable.choclate)
                    .setAutoCancel(true)
                    //显示在launcher上的数字
                    .setNumber(1)
                    .setContentIntent(mainPendingIntent);
            notificationManager.notify(id,builder.build());
        }
        else{
            NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "tag")
                    .setSmallIcon(R.drawable.choclate)
                    .setLargeIcon(bit)
                    .setContentTitle(content)
                    .setContentText(content + content + content + content)
                    .setContentIntent(mainPendingIntent).setAutoCancel(true)
            //This method was deprecated in API level 26. use enableVibration(boolean)
                    // and enableLights(boolean) and setSound(Uri, AudioAttributes) instead.
                    .setDefaults(Notification.DEFAULT_ALL);
            notificationManager.notify(id, builder.build());
        }
    }
}
