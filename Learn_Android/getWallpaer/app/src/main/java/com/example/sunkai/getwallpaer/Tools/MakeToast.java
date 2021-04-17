package com.example.sunkai.getwallpaer.Tools;

import android.widget.Toast;

/**
 * Created by sunkai on 2018/1/26.
 */

public class MakeToast {
    public static void Toast(String s){
        Toast.makeText(GlobalContext.context,s,Toast.LENGTH_SHORT).show();
    }
}
