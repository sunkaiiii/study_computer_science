package com.example.user.alarmmanager;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * Created by user on 2017/11/29.
 */

public class AlarmRecevier extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context,"闹钟响了",Toast.LENGTH_SHORT).show();
    }
}
