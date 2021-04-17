package com.example.user.packagemanager;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.graphics.drawable.Drawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    ListView listView;
    listViewAdapter adapter;

    private void init(){
        listView=(ListView)findViewById(R.id.list_view);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
        getAppInfo();
    }
    private void getAppInfo(){
        //获取一个PachageManager对象
        PackageManager pm=this.getPackageManager();
        //设置<intent-filter>标签内需要满足的条件
        Intent intent=new Intent(Intent.ACTION_MAIN,null);
        intent.addCategory(Intent.CATEGORY_DEFAULT);

        //通过queryIntentActivities获取ResolveInfo对象
        List<ResolveInfo> resolveInfos=pm.queryIntentActivities(intent,PackageManager.MATCH_DEFAULT_ONLY);

        Map<String,ResolveInfo> resultMap=new HashMap<>();
        List<ResolveInfo> infos=new ArrayList<>();
        for(ResolveInfo resolveInfo:resolveInfos){
            String appName=resolveInfo.loadLabel(pm).toString();
            Drawable dw= resolveInfo.loadIcon(pm);
            resultMap.put(appName,resolveInfo);
        }
        for(ResolveInfo info:resultMap.values()){
            infos.add(info);
        }
        adapter=new listViewAdapter(this,infos,pm);
        listView.setAdapter(adapter);
    }
}
