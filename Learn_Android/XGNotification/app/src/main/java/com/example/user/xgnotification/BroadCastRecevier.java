package com.example.user.xgnotification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by user on 2017/12/1.
 */

public class BroadCastRecevier extends BroadcastReceiver {
    private static final String TAG = "BroadCastRecevier";
    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context,"收到信息",Toast.LENGTH_SHORT).show();
        Log.d(TAG, "onReceive: 收到信息");
    }
}
