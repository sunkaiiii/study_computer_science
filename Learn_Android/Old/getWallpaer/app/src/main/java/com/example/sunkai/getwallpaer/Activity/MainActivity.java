package com.example.sunkai.getwallpaer.Activity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;

import com.example.sunkai.getwallpaer.Adapter.RecyclerViewAdapter;
import com.example.sunkai.getwallpaer.ConenctService.ConnectImageServiceBuilder;
import com.example.sunkai.getwallpaer.Data.imageData;
import com.example.sunkai.getwallpaer.R;
import com.example.sunkai.getwallpaer.Tools.MakeToast;
import com.example.sunkai.getwallpaer.Tools.Values;

import java.util.List;
import java.util.stream.Collector;

public class MainActivity extends AppCompatActivity {
    private List<imageData> datas;
    private RecyclerView recyclerView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        getImageInformations();
    }

    private void initView() {
        recyclerView = findViewById(R.id.recycler_view);
    }

    private void getImageInformations() {
        new Thread(() -> {
            try {
                datas = ConnectImageServiceBuilder.create(Values.IMAGE_URL).post();
                for (imageData data : datas) {
                    if (data.getUrl().equals("20130312")) {
                        data.setUrl(data.getUrl() + "!");
                    }
                }
                datas.stream()
                        .filter(data->data.getUrl().equals("20130312"))
                        .map(data->data.getUrl()+"!")
                        .collect(Collector.of()))
                runOnUiThread(() -> {
                    RecyclerViewAdapter adapter = new RecyclerViewAdapter(MainActivity.this, datas);
                    recyclerView.setLayoutManager(new GridLayoutManager(MainActivity.this, 2));
                    recyclerView.setAdapter(adapter);
                    MakeToast.Toast("成功");
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }
}
