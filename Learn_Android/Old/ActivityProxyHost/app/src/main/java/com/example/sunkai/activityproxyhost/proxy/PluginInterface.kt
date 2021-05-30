package com.example.sunkai.activityproxyhost.proxy

import android.app.Activity
import android.os.Bundle

/**
 * Created by sunkai on 2018/1/23.
 */
interface PluginInterface {
    fun IonStart()
    fun IonResume()
    fun IonPause()
    fun IonStop()
    fun IonDestroy()
    fun IonCreate(saveInstance: Bundle?)
    fun setProxy(proxyActivity: Activity)
}