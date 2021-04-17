package com.example.sunkai.viewpagertest

import android.app.Application
import android.content.Context
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.ActivityCompat
import android.support.v4.view.PagerAdapter
import android.support.v4.view.ViewPager
import android.view.View
import android.view.ViewGroup
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val viewpager=findViewById<ViewPager>(R.id.viewpager)
        val adapter=Adpter(IntArray(10).toList(),this)
        viewpager.adapter=adapter
    }


}
class Adpter(val data:List<Int>,private val context:Context):PagerAdapter(){
    override fun isViewFromObject(view: View?, `object`: Any?): Boolean {
        return view==`object`
    }

    override fun getCount(): Int {
        return data.size
    }

    override fun instantiateItem(container: ViewGroup?, position: Int): Any {
        val textView=TextView(context)
        textView.text = position.toString()
        container?.addView(textView)
        return textView
    }

    override fun destroyItem(container: ViewGroup?, position: Int, obj: Any?) {
        container?.removeView(obj as View)
    }
}

