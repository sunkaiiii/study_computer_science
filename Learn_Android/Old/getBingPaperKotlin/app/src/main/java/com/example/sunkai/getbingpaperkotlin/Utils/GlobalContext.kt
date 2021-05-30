package com.example.sunkai.getbingpaperkotlin.Utils

import android.annotation.SuppressLint
import android.app.Application
import android.content.Context

/*
 * Created by sunkai on 2018/1/22.
 */
class GlobalContext:Application() {
    companion object {
        @SuppressLint("StaticFieldLeak")
        lateinit var context:Context private set
    }
    override fun onCreate() {
        super.onCreate()
        context=this
    }
}