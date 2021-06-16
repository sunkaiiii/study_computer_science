package com.example.retrofit

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import java.lang.Exception

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        findViewById<Button>(R.id.getAppDataBtn).setOnClickListener {
            val retrofit = Retrofit.Builder()
                .baseUrl("https://sunkai.xyz:5001")
                .addConverterFactory(GsonConverterFactory.create())
                .build()
            val appService = retrofit.create(AppService::class.java)
            appService.getAppData().enqueue(object:Callback<List<MainPageBanner>>{
                override fun onResponse(
                    call: Call<List<MainPageBanner>>,
                    response: Response<List<MainPageBanner>>
                ) {
                    val list = response.body()
                    println(list)
                }

                override fun onFailure(call: Call<List<MainPageBanner>>, t: Throwable) {
                    t.printStackTrace()
                }
            })
        }
        findViewById<Button>(R.id.getNewsList).setOnClickListener {
            val appService = ServiceCreator.create<AppService>()
            appService.getNewsList(1).enqueue(object :Callback<List<NewsListResponse>>{
                override fun onResponse(
                    call: Call<List<NewsListResponse>>,
                    response: Response<List<NewsListResponse>>
                ) {
                    Toast.makeText(this@MainActivity, "News list returned", Toast.LENGTH_SHORT).show()
                }

                override fun onFailure(call: Call<List<NewsListResponse>>, t: Throwable) {

                }

            })
        }

        findViewById<Button>(R.id.getNewsDetail).setOnClickListener {

        }
    }

    suspend fun getDetail(){
        try {
            val newsDetail = ServiceCreator.create<AppService>().getNewsDetail("test_id").await()
        }catch (e:Exception){
            e.printStackTrace()
        }
    }
}