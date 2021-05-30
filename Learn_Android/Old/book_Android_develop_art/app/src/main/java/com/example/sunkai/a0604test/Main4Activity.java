package com.example.sunkai.a0604test;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.TransitionDrawable;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.RemoteViews;

public class Main4Activity extends AppCompatActivity {
    NotificationManager manager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main4);
        findViewById(R.id.notifyButton).setOnClickListener((v)->{
            Notification notification=new Notification();
            notification.icon=R.drawable.ic_loyalty_white_24dp;
            notification.tickerText="hello world";
            notification.when=System.currentTimeMillis();
            notification.flags=Notification.FLAG_AUTO_CANCEL;
            Intent intent=new Intent(this,MainActivity.class);
            PendingIntent pendingIntent=PendingIntent.getActivity(this,0,intent,PendingIntent.FLAG_UPDATE_CURRENT);
            RemoteViews remoteViews=new RemoteViews(getPackageName(),R.layout.notification_layout);
            remoteViews.setTextViewText(R.id.notify_textview,"adasd");
            remoteViews.setImageViewResource(R.id.notify_imageview,R.drawable.ic_warning_pink_300_24dp);
            PendingIntent openActivity2PendingIntent=PendingIntent.getActivity(this,0,new Intent(this,MainActivity.class),PendingIntent.FLAG_UPDATE_CURRENT);
            notification.contentView=remoteViews;
            notification.contentIntent=pendingIntent;
            manager=(NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                createNotifycationChannel();
            }
            manager.notify(1,notification);
        });
        findViewById(R.id.showtransition).setOnClickListener(v -> ((TransitionDrawable)findViewById(R.id.transition_imageview).getBackground()).startTransition(300));

    }


    @RequiresApi(api = Build.VERSION_CODES.O)
    private void createNotifycationChannel(){
        NotificationChannel channel=new NotificationChannel("1","channel",NotificationManager.IMPORTANCE_DEFAULT);
        channel.enableLights(true);
        channel.setLightColor(getColor(R.color.colorPrimary));
        channel.setShowBadge(true); //是否显示通知角标
        manager.createNotificationChannel(channel);
    }

    @Override
    public void finish() {
        super.finish();
        overridePendingTransition(R.anim.enter_animation,R.anim.exit_animation);
    }
}
