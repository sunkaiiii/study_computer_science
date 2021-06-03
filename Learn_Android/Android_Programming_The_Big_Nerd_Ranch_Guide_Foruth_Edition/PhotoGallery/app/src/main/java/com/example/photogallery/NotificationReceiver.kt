package com.example.photogallery

import android.app.Activity
import android.app.Notification
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.util.Log
import androidx.core.app.NotificationManagerCompat

private const val TAG = "NotificationReceiver"
class NotificationReceiver:BroadcastReceiver() {
    override fun onReceive(context: Context?, intent: Intent?) {
        if (resultCode != Activity.RESULT_OK) {
            // A foreground activity canceled the broadcast
            return }
        val requestCode = intent?.getIntExtra(PollWorker.REQUEST_CODE, 0 )?:return
        val notification: Notification =
            intent.getParcelableExtra(PollWorker.NOTIFICATION) ?:return
        val notificationManager = NotificationManagerCompat.from(context?:return)
        notificationManager.notify(requestCode, notification)
    }
}