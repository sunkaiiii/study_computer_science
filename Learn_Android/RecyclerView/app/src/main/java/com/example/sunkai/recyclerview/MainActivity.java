package com.example.sunkai.recyclerview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class MainActivity extends AppCompatActivity {
    RecyclerView recycleListView;
    List<String> lists;
    Adpter adpter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
//        LinearLayoutManager layoutManager=new LinearLayoutManager(this);
//        layoutManager.setOrientation(LinearLayoutManager.HORIZONTAL); //变为一个横向滚动布局
//        recycleListView.setLayoutManager(layoutManager); //设置recycler的布局方式，这里用的是线性布局
//        adpter=new Adpter(lists);
//        recycleListView.setAdapter(adpter);

        //第二种布局方法，实现一个瀑布流布局
//        StaggeredGridLayoutManager layoutManager=new StaggeredGridLayoutManager(3,StaggeredGridLayoutManager.VERTICAL);
//        adpter=new Adpter(lists);
//        recycleListView.setLayoutManager(layoutManager);
//        recycleListView.setAdapter(adpter);

        //第三种方法，实现一个网格布局
        GridLayoutManager layoutManager=new GridLayoutManager(this,4);
        adpter=new Adpter(lists);
        recycleListView.setLayoutManager(layoutManager);
        recycleListView.setAdapter(adpter);
    }
    private void init(){
        recycleListView=findViewById(R.id.recycler_view);
        lists=new ArrayList<>();
        lists=IntStream.range(0,100).mapToObj(eachInt->String.valueOf(eachInt)).collect(Collectors.toList());
    }
}
