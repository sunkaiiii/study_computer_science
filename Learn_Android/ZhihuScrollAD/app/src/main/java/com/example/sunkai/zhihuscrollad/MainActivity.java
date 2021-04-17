package com.example.sunkai.zhihuscrollad;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;

import com.zhy.adapter.recyclerview.CommonAdapter;
import com.zhy.adapter.recyclerview.base.ViewHolder;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private RecyclerView mRecyclerView;
    private LinearLayoutManager mLinearLayoutManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mRecyclerView=findViewById(R.id.id_recyclerview);
        List<String> strings=new ArrayList<>();
        for(int i=0;i<100;i++){
            strings.add(i+"");
        }
        mRecyclerView.setLayoutManager(mLinearLayoutManager=new LinearLayoutManager(this));
        mRecyclerView.setAdapter(new CommonAdapter<String>(MainActivity.this,R.layout.list_item,strings) {
            @Override
            protected void convert(ViewHolder holder, String o, int position) {
                if(position==6){
                    holder.setVisible(R.id.id_tv_title,false);
                    holder.setVisible(R.id.id_tv_desc,false);
                    holder.setVisible(R.id.id_iv_ad,true);
                }
                else{
                    holder.setVisible(R.id.id_tv_title,true);
                    holder.setVisible(R.id.id_tv_desc,true);
                    holder.setVisible(R.id.id_iv_ad,false);
                }
            }
        });
        mRecyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
            @Override
            public void onScrolled(RecyclerView recyclerView, int dx, int dy) {
                super.onScrolled(recyclerView, dx, dy);
                int fPos=mLinearLayoutManager.findFirstVisibleItemPosition();
                int lPos=mLinearLayoutManager.findLastCompletelyVisibleItemPosition();
                for(int i=fPos;i<lPos;i++){
                    View view=mLinearLayoutManager.findViewByPosition(i);
                    AdImageView adImageViewVersion1=view.findViewById(R.id.id_iv_ad);
                    if(adImageViewVersion1.getVisibility()==View.VISIBLE){
                        adImageViewVersion1.setDx(mLinearLayoutManager.getHeight()-view.getTop());
                    }
                }
            }
        });
    }
}
