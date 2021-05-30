package com.example.user.fcm;

import android.util.Log;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

/**
 * Created by user on 2017/12/4.
 */

public class MyFCMMessageService extends FirebaseMessagingService {
    private static final String TAG = "MyFCMMessageService";
    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
        super.onMessageReceived(remoteMessage);
        Log.d(TAG,"from:"+remoteMessage.getFrom());

        if(remoteMessage.getData().size()>0){
            Log.d(TAG, "onMessageReceived: "+remoteMessage.getData());
        }

        if(remoteMessage.getNotification()!=null){
            Log.d(TAG, "onMessageReceived: Notification"+remoteMessage.getNotification().getBody());
        }
    }
}
