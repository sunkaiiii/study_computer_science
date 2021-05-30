package com.example.sunkai.aboutactivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends BaseActivity {
    private Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=findViewById(R.id.button1);
        button.setOnClickListener(view -> {
            Intent intent=new Intent(MainActivity.this,Main2Activity.class);
            startActivity(intent);
        });
    }
}
