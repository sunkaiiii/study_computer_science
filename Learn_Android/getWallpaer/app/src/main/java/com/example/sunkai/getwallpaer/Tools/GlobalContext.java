package com.example.sunkai.getwallpaer.Tools;

import android.app.Application;
import android.content.Context;

/**
 * Created by sunkai on 2018/1/26.
 */

public class GlobalContext extends Application {
    public static Context context;

    @Override
    public void onCreate() {
        super.onCreate();
        context=getApplicationContext();
    }
}
