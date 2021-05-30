package com.example.sunkai.materialdesignkits;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;

import java.util.List;

/**
 * Created by sunkai on 2017/12/26.
 */

public class FruitAdpter extends RecyclerView.Adapter<FruitAdpter.ViewHolder> {
    private Context context;
    private List<Fruit> mFruitList;
    static class ViewHolder extends RecyclerView.ViewHolder{
        CardView cardView;
        ImageView fruitImage;
        TextView fruitName;
        public ViewHolder(View view){
            super(view);
            cardView=(CardView)view;
            fruitImage=view.findViewById(R.id.fruit_image);
            fruitName=view.findViewById(R.id.fruit_name);
        }
    }
    public FruitAdpter(List<Fruit> fruitList){
        mFruitList=fruitList;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        if(context==null)
            context=parent.getContext();
        View view= LayoutInflater.from(context).inflate(R.layout.fruit_item,parent,false);
        final ViewHolder holder=new ViewHolder(view);
        holder.cardView.setOnClickListener((v)->{
            int postion=holder.getAdapterPosition();
            Fruit fruit=mFruitList.get(postion);
            Intent intent=new Intent(context,FruitActivity.class);
            intent.putExtra(FruitActivity.FRUIT_NAME,fruit.getName());
            intent.putExtra(FruitActivity.FRUIT_IMAGE_ID,fruit.getImageID());
            context.startActivity(intent);
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        Fruit fruit=mFruitList.get(position);
        holder.fruitName.setText(fruit.getName());
        Glide.with(context).load(fruit.getImageID()).into(holder.fruitImage);
    }

    @Override
    public int getItemCount() {
        return mFruitList.size();
    }
}
