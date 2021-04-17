package com.example.sunkai.recyclerview;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

/**
 * Created by sunkai on 2017/12/18.
 *
 */

public class Adpter extends RecyclerView.Adapter<Adpter.ViewHolder> {
    private List<String> lists;
    static class ViewHolder extends RecyclerView.ViewHolder{
        TextView textView;
        View view;
        private ViewHolder(View view){
            super(view);
            textView=view.findViewById(R.id.textview);
            this.view=view;
        }
    }
    public Adpter(List<String> lists){
        this.lists=lists;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view= LayoutInflater.from(parent.getContext()).inflate(R.layout.item,parent,false);
        final ViewHolder holder=new ViewHolder(view);
        holder.textView.setOnClickListener((v)->{ //设置一个监听事件
            int postion=holder.getAdapterPosition();
            String s=lists.get(postion);
            Toast.makeText(v.getContext(), s, Toast.LENGTH_SHORT).show();
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        String s=lists.get(position);
        holder.textView.setText(s);
    }

    @Override
    public int getItemCount() {
        return lists.size();
    }
}
