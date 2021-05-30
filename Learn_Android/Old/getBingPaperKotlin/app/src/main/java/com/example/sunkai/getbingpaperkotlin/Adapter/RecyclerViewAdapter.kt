package com.example.sunkai.getbingpaperkotlin.Adapter

import android.content.Context
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import com.bumptech.glide.Glide
import com.example.sunkai.getbingpaperkotlin.Data.ImageData
import com.example.sunkai.getbingpaperkotlin.R
import kotlinx.android.synthetic.main.item_layout.view.*

/**
 * Created by sunkai on 2018/1/22.
 */
class RecyclerViewAdapter(val context: Context, var datas:List<ImageData>):RecyclerView.Adapter<RecyclerViewAdapter.Holder>() {

    class Holder(view: View):RecyclerView.ViewHolder(view){
        val textView:TextView = view.findViewById(R.id.item_title)
        val imageView:ImageView = view.findViewById(R.id.item_image)
    }

    override fun onCreateViewHolder(parent: ViewGroup?, viewType: Int): Holder {
        val view=LayoutInflater.from(context).inflate(R.layout.item_layout,parent,false)
        return Holder(view)
    }

    override fun getItemCount(): Int {
        return datas.size
    }

    override fun onBindViewHolder(holder: Holder?, position: Int) {
        holder?.let{
            val data=datas[position]
            holder.textView.text=data.copyright
            Glide.with(context).load(data.url).into(holder.imageView)
        }
    }

}