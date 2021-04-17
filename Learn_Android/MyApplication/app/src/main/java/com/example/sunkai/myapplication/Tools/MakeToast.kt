package com.example.sunkai.myapplication.Tools

import android.app.Activity

/*
 * Created by sunkai on 2018/1/26.
 */

fun Activity.Toast(str:String){
    android.widget.Toast.makeText(GlobalContext.context,str,android.widget.Toast.LENGTH_SHORT).show()
}