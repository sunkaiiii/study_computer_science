package com.example.sunkai.activityproxyhost.myapplicaiton

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.os.Environment
import android.widget.Toast
import com.example.sunkai.activityproxyhost.R
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        Toast.makeText(this,Environment.getExternalStorageDirectory().absolutePath,Toast.LENGTH_LONG).show()
        btn_reflect.setOnClickListener {
            val intent=Intent(this,ProxyActivity::class.java)
            startActivity(intent)
        }

        btn_interface.setOnClickListener{
            val intent=Intent(this,PlugProxyActivity::class.java)
            startActivity(intent)
        }
    }
}
