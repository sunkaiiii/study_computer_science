package com.example.sunkai.getbingpaperkotlin.Utils

import android.app.Activity
import android.support.v4.app.Fragment
import android.widget.Toast

/**
 * Created by sunkai on 2018/1/22.
 */

private fun MakeToast(text:String){
    Toast.makeText(GlobalContext.context,text,Toast.LENGTH_SHORT).show()
}

//fun Activity.MakeToast(text:String){
//    MakeToast(text)
//}
//
//fun Fragment.MakeToast(text:String){
//    MakeToast(text)
//}

fun Any.MakeToast(text:String){
    com.example.sunkai.getbingpaperkotlin.Utils.MakeToast(text)
}
