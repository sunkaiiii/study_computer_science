package com.example.sunkai.materialdesignkits;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.NavigationView;
import android.support.design.widget.Snackbar;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MainActivity extends AppCompatActivity {
    private DrawerLayout mDrawerLayout;
    private Fruit[] fruits={
            new Fruit("Apple",R.drawable.apple),
            new Fruit("Banana",R.drawable.banana),
            new Fruit("Orange",R.drawable.orange),
            new Fruit("Grape",R.drawable.grape),
            new Fruit("Pineapple",R.drawable.pineapple),
            new Fruit("Strawberry",R.drawable.strawberry),
            new Fruit("Cherry",R.drawable.cherry),
            new Fruit("Mange",R.drawable.mango)
    };
    private List<Fruit> fruitList=new ArrayList<>();
    private FruitAdpter adpter;
    private SwipeRefreshLayout swipeRefreshLayout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar=findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        mDrawerLayout=findViewById(R.id.drawer_layout);
        NavigationView navView=findViewById(R.id.nav_view);
        ActionBar actionBar=getSupportActionBar();
        FloatingActionButton fab=findViewById(R.id.fab);
        swipeRefreshLayout=findViewById(R.id.swipe_refresh);
        swipeRefreshLayout.setColorSchemeResources(R.color.colorPrimary);
        swipeRefreshLayout.setOnRefreshListener(()-> refreshFruits());
        fab.setOnClickListener((v)-> Snackbar.make(v,"Data deleted",Snackbar.LENGTH_SHORT)
                .setAction("Undo",(view -> Toast.makeText(MainActivity.this,"Data restored",Toast.LENGTH_SHORT)
                        .show()))
                .show());
        if(actionBar!=null){
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setHomeAsUpIndicator(R.drawable.ic_menu_white_24dp);
        }
        navView.setCheckedItem(R.id.nav_call); //默认选择call这个菜单
        navView.setNavigationItemSelectedListener(item -> {
            mDrawerLayout.closeDrawers(); //选中任意一个菜单项之后收起菜单
            return true;
        });
        initFruits();
        RecyclerView recyclerView=findViewById(R.id.recycler_view);
        GridLayoutManager layoutManager=new GridLayoutManager(this,2);
        recyclerView.setLayoutManager(layoutManager);
        adpter=new FruitAdpter(fruitList);
        recyclerView.setAdapter(adpter);
    }

    private void initFruits(){
        fruitList.clear();
        for(int i=0;i<50;i++){
            Random random=new Random();
            int index=random.nextInt(fruits.length);
            fruitList.add(fruits[index]);
        }
    }

    private void refreshFruits(){
        new Thread(()->{
            try{
                Thread.sleep(2000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
            runOnUiThread(()->{
                initFruits();
                adpter.notifyDataSetChanged();
                swipeRefreshLayout.setRefreshing(false);
            });
        }).start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.toolbar,menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        //显示侧边菜单
        switch (item.getItemId()){
            case android.R.id.home:
                mDrawerLayout.openDrawer(GravityCompat.START);
                break;
        }
        return true;
    }
}
