package com.example.sunkai.myapplication.Adapter

import android.content.Context
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import com.bumptech.glide.Glide
import com.example.sunkai.myapplication.Data.imageData
import com.example.sunkai.myapplication.R

/*
 * Created by sunkai on 2018/1/26.
 */
class RecyclerViewAdapter(val context: Context, val datas:List<imageData>):RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup?, viewType: Int): ViewHolder {
        val view=LayoutInflater.from(context).inflate(R.layout.item_layout,parent,false)
        return ViewHolder(view)
    }

    override fun getItemCount(): Int {
        return datas.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val data=datas[position]
        holder.copyRight.text=data.copyright
        data.ok
        Glide.with(context).load(data.url).into(holder.image)
    }

    class ViewHolder(view: View):RecyclerView.ViewHolder(view){
        val copyRight:TextView
        val image:ImageView
        init {
            copyRight=view.findViewById<TextView>(R.id.item_title)
            image=view.findViewById<ImageView>(R.id.item_image)
        }
    }
}