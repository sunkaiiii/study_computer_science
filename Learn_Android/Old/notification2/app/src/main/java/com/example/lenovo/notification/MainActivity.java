package com.example.lenovo.notification;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button bUtton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bUtton=findViewById(R.id.button);
        bUtton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendNotification();
            }
        });


    }
    private void sendNotification(){
        Intent intent=new Intent(this,MainActivity.class);
        PendingIntent pi= PendingIntent.getActivity(this,0,intent,0);
        Notification notification=new NotificationCompat.Builder(this,"channel 1")
                .setContentTitle("This is content title")
                .setContentText("this is content text")
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setWhen(System.currentTimeMillis())
                .setContentIntent(pi)
                .setAutoCancel(true)
                .setVibrate(new long[]{0,1000,1000,1000,1000}) //设置震动时长
                .setLights(Color.YELLOW,1000,1000) //设置通知灯
                .setStyle(new NotificationCompat.BigPictureStyle().bigPicture(BitmapFactory.decodeResource(getResources(),R.drawable.ic_launcher_background))) //将通知内容改为显示一个图片
                .setPriority(NotificationCompat.PRIORITY_MAX)
                .build();
        NotificationManager manager=(NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        manager.notify(1,notification);
    }
}
