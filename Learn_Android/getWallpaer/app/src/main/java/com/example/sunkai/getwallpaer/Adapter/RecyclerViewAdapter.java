package com.example.sunkai.getwallpaer.Adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.example.sunkai.getwallpaer.Data.imageData;
import com.example.sunkai.getwallpaer.R;

import java.util.List;

/*
 * Created by sunkai on 2018/1/26.
 */

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder> {


    private Context context;
    private List<imageData> datas;
    public RecyclerViewAdapter(final Context context, final List<imageData> datas){
        this.context=context;
        this.datas=datas;
    }
    @Override
    public RecyclerViewAdapter.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view= LayoutInflater.from(context).inflate(R.layout.item_layout,parent,false);
        return new ViewHolder(view);
    }
    @Override
    public void onBindViewHolder(RecyclerViewAdapter.ViewHolder holder, int position) {
        imageData data=datas.get(position);
        holder.copyRight.setText(data.getCopyright());
        Glide.with(context).load(data.getUrl()).into(holder.image);

    }

    @Override
    public int getItemCount() {
        return datas.size();
    }

    class ViewHolder extends RecyclerView.ViewHolder{
        TextView copyRight;
        ImageView image;
        public ViewHolder(View view){
            super(view);
            copyRight=view.findViewById(R.id.item_title);
            image=view.findViewById(R.id.item_image);
        }
    }
}
