package com.example.sunkai.myapplication.ConnectWebService

import com.example.sunkai.myapplication.Data.imageData
import com.google.gson.Gson
import com.google.gson.reflect.TypeToken
import okhttp3.OkHttpClient
import okhttp3.Request
import java.io.IOException

/**
 * Created by sunkai on 2018/1/26.
 */


fun GetImageData(url:String,`when`:Int=0,count:Int=30):List<imageData>{
    val request = Request.Builder().url("$url?count=$count&when=$`when`").build()
    val client = OkHttpClient()
    try {
        val response = client.newCall(request).execute()
        val body = response.body()
        body?.let{
            val gson = Gson()
            return gson.fromJson(body.string(), object : TypeToken<List<imageData>>() {
            }.type)
        }


    } catch (e: IOException) {
        e.printStackTrace()
    }
    return ArrayList<imageData>()
}