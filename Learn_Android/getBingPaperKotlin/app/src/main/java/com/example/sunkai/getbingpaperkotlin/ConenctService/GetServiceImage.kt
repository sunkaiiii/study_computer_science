package com.example.sunkai.getbingpaperkotlin.ConenctService

import com.example.sunkai.getbingpaperkotlin.Data.ImageData
import com.google.gson.Gson
import okhttp3.OkHttpClient
import okhttp3.Request
import java.io.IOException

/*
 * Created by sunkai on 2018/1/22.
 */
object GetServiceImage {
    private val client=OkHttpClient()


    private fun <T> Gson.fromJsonToList(json: String, clazz: Class<Array<T>>):List<T>{
        val arr=Gson().fromJson(json,clazz)
        return arr.toList()
    }

    fun GetImageFromServer(url:String,`when`:Int=0,count:Int=30):List<ImageData>{
        val request=Request.Builder().url(url+"?when="+`when`.toString()+"&count="+count.toString()).build()
        try{
            val response= client.newCall(request).execute()
            if(response.isSuccessful){

                val result=response.body()
                result?.let{
                    return Gson().fromJsonToList(result.string(), Array<ImageData>::class.java)
                }

            }
        }catch (e:IOException){
            e.printStackTrace()
        }
        return ArrayList()
    }
}
