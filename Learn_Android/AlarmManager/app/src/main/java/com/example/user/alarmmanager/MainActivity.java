package com.example.user.alarmmanager;

import android.annotation.SuppressLint;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

    @BindView(R.id.ELAPSED_REALTIME_CLOCK)
    Button ELAPSEDREALTIMECLOCK;
    @BindView(R.id.ELAPSED_REALTIME_WAKEUP_CLOCK)
    Button ELAPSEDREALTIMEWAKEUPCLOCK;
    @BindView(R.id.RTC_CLOCK)
    Button RTCCLOCK;
    @BindView(R.id.RTC_WAKEUP_CLOCK)
    Button RTCWAKEUPCLOCK;
    @BindView(R.id.repeating_clock)
    Button repeatingClock;
    @BindView(R.id.cancel_clock)
    Button cancelClock;
    private AlarmManager alarmManager;
    private PendingIntent operation;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);


        //获取AlmarManager对象
        alarmManager=(AlarmManager)getSystemService(ALARM_SERVICE);

        Intent intent=new Intent("android.intent.action.ALARM_RECEVIER");
        if(Build.VERSION.SDK_INT>=26){
            intent.setClassName("com.example.user.alarmmanager","com.example.user.alarmmanager.AlarmRecevier");
        }
        operation=PendingIntent.getBroadcast(this,0,intent,0);


    }

    @OnClick({R.id.ELAPSED_REALTIME_CLOCK, R.id.ELAPSED_REALTIME_WAKEUP_CLOCK, R.id.RTC_CLOCK, R.id.RTC_WAKEUP_CLOCK, R.id.repeating_clock, R.id.cancel_clock})
    public void onViewClicked(View view) {
        switch (view.getId()) {
            case R.id.ELAPSED_REALTIME_CLOCK:
                //在指定的延时后，发送广播，并唤醒设备
                //延时是要吧系统启动时间SystemClock.elapsedReadltime()算进去
                int triggerAtTime=(int)(SystemClock.elapsedRealtime()+10*1000);
                alarmManager.set(AlarmManager.ELAPSED_REALTIME,triggerAtTime,operation);
                break;
            case R.id.ELAPSED_REALTIME_WAKEUP_CLOCK:
                //在指定的延时后，发送广播，并唤醒设备
                int triggerAtTime1=(int)(SystemClock.elapsedRealtime()+10*1000);
                alarmManager.set(AlarmManager.ELAPSED_REALTIME_WAKEUP,triggerAtTime1,operation);
                break;
            case R.id.RTC_CLOCK:
                //在指定的时刻，发送广播，但不唤醒设备
                alarmManager.set(AlarmManager.RTC_WAKEUP,getDateMills("2017-11-29 18:02:00"),operation);
                break;
            case R.id.RTC_WAKEUP_CLOCK:
                //在指定的时刻，发送广播，并唤醒设备
                alarmManager.set(AlarmManager.RTC_WAKEUP,getDateMills("2017-11-29 18:02:50"),operation);
                break;
            case R.id.repeating_clock:
                //设置重复闹钟
                alarmManager.setRepeating(AlarmManager.RTC_WAKEUP,500,10000,operation);
                break;
            case R.id.cancel_clock:
                alarmManager.cancel(operation);
                break;
        }
    }
    @SuppressLint("SimpleDateFormat")
    public long getDateMills(String dateStr) {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd kk:mm:ss");
        Date date;
        try {
            date = format.parse(dateStr);
            return date.getTime();
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return 0;
    }
}
