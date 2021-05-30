package com.example.user.androidtint;

import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    ImageView img1,img2,img3,img4;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        img1=(ImageView)findViewById(R.id.image1);
        img2=(ImageView)findViewById(R.id.image2);
        img3=(ImageView)findViewById(R.id.image3);
        img4=(ImageView)findViewById(R.id.image4);

        img1.setColorFilter(0x50ff00ff, PorterDuff.Mode.SRC);
        img2.setColorFilter(0x50ff00ff, PorterDuff.Mode.SRC_OVER);
        img3.setColorFilter(0x50ff00ff, PorterDuff.Mode.MULTIPLY);
        img4.setColorFilter(0x50ff00ff, PorterDuff.Mode.SRC_IN);
    }
}
