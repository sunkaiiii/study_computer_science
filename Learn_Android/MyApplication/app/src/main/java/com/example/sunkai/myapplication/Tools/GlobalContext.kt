package com.example.sunkai.myapplication.Tools

import android.app.Application
import android.content.Context

/**
 * Created by sunkai on 2018/1/26.
 */
class GlobalContext:Application(){
    companion object {
        lateinit var context:Context
    }

    override fun onCreate() {
        super.onCreate()
        context=applicationContext
    }
}