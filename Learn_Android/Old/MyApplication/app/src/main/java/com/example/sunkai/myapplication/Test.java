package com.example.sunkai.myapplication;

import com.example.sunkai.myapplication.Data.imageData;
import com.example.sunkai.myapplication.Tools.GlobalContext;

/**
 * Created by sunkai on 2018/1/26.
 */

public class Test {
    void funtion(){
        imageData data=new imageData("123","123","13");
        data.getCopyright();
        GlobalContext.Companion.getContext();
    }
}
