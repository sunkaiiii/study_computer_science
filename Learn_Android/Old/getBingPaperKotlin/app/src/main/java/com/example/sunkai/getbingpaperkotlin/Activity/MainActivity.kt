package com.example.sunkai.getbingpaperkotlin.Activity

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.GridLayoutManager
import com.example.sunkai.getbingpaperkotlin.Adapter.RecyclerViewAdapter
import com.example.sunkai.getbingpaperkotlin.ConenctService.GetServiceImage
import com.example.sunkai.getbingpaperkotlin.Interface.OnPageLoad
import com.example.sunkai.getbingpaperkotlin.R
import com.example.sunkai.getbingpaperkotlin.Utils.CONNECT_URL
import com.example.sunkai.getbingpaperkotlin.Utils.MakeToast
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity(),OnPageLoad {


    override fun onCreate(savedInstanceState: Bundle?){
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        initView()
        startGetInformation()
    }

    private fun initView(){
        recycler_view.layoutManager=GridLayoutManager(this,2)
        refresh_layout.setOnRefreshListener {
            startGetInformation()
        }
    }

    private fun startGetInformation(){
        onPreLoad()
        Thread{
            val datas=GetServiceImage.GetImageFromServer(CONNECT_URL)
            runOnUiThread {
                onPostLoad()
                val adapter=RecyclerViewAdapter(this,datas)
                recycler_view.adapter=adapter
            }
        }.start()
    }

    override fun onPreLoad() {
        recycler_view.adapter=null
        refresh_layout.isRefreshing=true
    }

    override fun onPostLoad() {
        refresh_layout.isRefreshing=false
        MakeToast("获取数据")
    }
}
