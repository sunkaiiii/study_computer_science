package com.example.sunkai.aboutactivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

public class Main2Activity extends BaseActivity {
    private Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        button=findViewById(R.id.button2);
        button.setOnClickListener(view -> {
            Intent intent=new Intent(Main2Activity.this,Main3Activity.class);
            startActivity(intent);
        });
    }
}
