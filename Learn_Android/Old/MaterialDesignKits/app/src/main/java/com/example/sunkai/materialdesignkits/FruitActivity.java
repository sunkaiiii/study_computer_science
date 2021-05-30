package com.example.sunkai.materialdesignkits;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.CollapsingToolbarLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;

import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * Created by sunkai on 2017/12/26.
 */

public class FruitActivity extends AppCompatActivity {
    public static final String FRUIT_NAME="fruit_name";
    public static final String FRUIT_IMAGE_ID="fruit_image_id";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fruit);
        Intent intent=getIntent();
        String fruitName=intent.getStringExtra(FRUIT_NAME);
        int fruitImageID=intent.getIntExtra(FRUIT_IMAGE_ID,0);
        Toolbar toolbar=findViewById(R.id.toolbar);
        CollapsingToolbarLayout collapsingToolbarLayout=findViewById(R.id.collapsing_toolbar);
        ImageView imageView=findViewById(R.id.fruit_image_view);
        TextView textView=findViewById(R.id.fruit_content_text);
        setSupportActionBar(toolbar);
        ActionBar actionBar=getSupportActionBar();
        if(actionBar!=null){
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
        collapsingToolbarLayout.setTitle(fruitName);
        Glide.with(this).load(fruitImageID).into(imageView);
        String fruitContent=generateFruitContent(fruitName);
        textView.setText(fruitContent);
    }

    private String generateFruitContent(String fruitName){
        StringBuilder sb=new StringBuilder();
        for(int i=0;i<500;i++){
            sb.append(fruitName);
        }
        return sb.toString();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case android.R.id.home:
                finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
