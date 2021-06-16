package com.example.retrofit

import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.GET
import retrofit2.http.Path
import retrofit2.http.Query
import java.io.Serializable
import kotlin.coroutines.resume
import kotlin.coroutines.resumeWithException
import kotlin.coroutines.suspendCoroutine

class MainPageBanner(val link:String, val img:String,val compressImg:String?)

class NewsListResponse(val link: String,
                       val title: String,
                       val date: String,
                       val content: String,
                       var img: String?,
                       var compressImg: String?,
                       var isRead: Boolean = false,
                       var idFromDataBase: Int?,
                       var typeFromDatabase: String?)

class NewsDetail(val link: String,
                 val title: String,
                 val subtitle: List<String>?,
                 val time: String?,
                 val author: String,
                 var content: List<NewsDetailContent>,
                 var relativeNews: List<NewsDetailRelativeNews>)
class NewsDetailContent(val type: String, val content: String, val compressImg: String?)
class NewsDetailRelativeNews(val link: String, val date: String, val title: String)

interface AppService{
    @GET("/api/Banner")
    fun getAppData():Call<List<MainPageBanner>>

    @GET("/api/NewsList/{page}")
    fun getNewsList(@Path("page") page:Int):Call<List<NewsListResponse>>

    @GET("/api/NewsDetail")
    fun getNewsDetail(@Query("id")id:String):Call<NewsDetail>
}

object ServiceCreator{
    private const val BASE_URL = "https://sunkai.xyz:5001"

    private val retrofit = Retrofit.Builder()
        .baseUrl(BASE_URL)
        .addConverterFactory(GsonConverterFactory.create())
        .build()
    fun <T> create(serviceClass:Class<T>):T = retrofit.create(serviceClass)

    inline fun <reified T> create():T= create(T::class.java)

}

//使用协程来改进retrofit
suspend fun <T> Call<T>.await():T{
    return suspendCoroutine { continuation ->
        enqueue(object:Callback<T>{
            override fun onResponse(call: Call<T>, response: Response<T>) {
                val body = response.body()
                if(body!=null){
                    continuation.resume(body)
                }else{
                    continuation.resumeWithException(RuntimeException("response body is null"))
                }
            }

            override fun onFailure(call: Call<T>, t: Throwable) {
                continuation.resumeWithException(t)
            }

        })
    }
}