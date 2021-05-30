package com.example.sunkai.aboutactivity;

import android.app.Activity;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by sunkai on 2017/12/18.
 */

public class ActivityCollector {
    public static List<Activity> activities=new ArrayList<>();
    public static void addActivity(Activity activity){
        activities.add(activity);
    }
    public static void removeActivity(Activity activity){
        activities.remove(activity);
    }
    public static void finishAll(){
        activities.stream().filter(activity->!activity.isFinishing()).forEach(activity -> activity.finish());
        activities.clear();
    }
}
