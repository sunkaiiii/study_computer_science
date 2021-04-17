package com.example.sunkai.myapplication

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.GridLayoutManager
import android.view.View
import android.widget.AdapterView
import com.example.sunkai.myapplication.Adapter.RecyclerViewAdapter
import com.example.sunkai.myapplication.ConnectWebService.GetImageData
import com.example.sunkai.myapplication.Data.IMAGE_URL
import com.example.sunkai.myapplication.Interface.itemClick
import com.example.sunkai.myapplication.Tools.Toast
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity(),View.OnClickListener {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        getInformation()
    }
    private fun getInformation(){
        Thread{
            val datas= GetImageData(IMAGE_URL)
            runOnUiThread {
                val adpter=RecyclerViewAdapter(this@MainActivity,datas)
                Toast("刷新完成")
                recycler_view.layoutManager=GridLayoutManager(this,2)
                recycler_view.adapter=adpter
            }
        }.start()
    }

    override fun onClick(v: View?) {

    }
}
