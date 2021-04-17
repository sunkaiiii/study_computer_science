package com.example.sunkai.aboutactivity;

import android.os.Bundle;
import android.widget.Button;

public class Main3Activity extends BaseActivity {
    private Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);
        button=findViewById(R.id.button3);
        button.setOnClickListener((view -> {
            ActivityCollector.finishAll(); //清除所有活动的activity
        }));
    }
}
