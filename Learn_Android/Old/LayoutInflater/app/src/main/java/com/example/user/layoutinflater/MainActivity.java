package com.example.user.layoutinflater;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private LinearLayout mLiContainer;
    private LayoutInflater mInflater;
    private static final String TAG="MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_root_is_not_null).setOnClickListener(this);
        findViewById(R.id.btn_root_is_null).setOnClickListener(this);

        mLiContainer=(LinearLayout)findViewById(R.id.ll_container);
//        获取LayoutInflater实例
//        也可以通过this.getSystemService(Context.LAYOUT_INFLATER_SERVICE)来获取
        mInflater=LayoutInflater.from(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btn_root_is_not_null:
                inflateWithRoot();
                break;
            case R.id.btn_root_is_null:
                inflateWithoutRoot();
                break;
        }
    }

//    使用inflate（int resourse,ViewGroup root)载入布局
    private void inflateWithRoot(){
        View inflateView=mInflater.inflate(R.layout.layout_single_button,mLiContainer);
        Log.d(TAG, "inflateWithRoot: infalterView type="+inflateView.getClass().getSimpleName());
    }

    private void inflateWithoutRoot(){
        View inflateView=mInflater.inflate(R.layout.layout_single_button,null);
        Log.d(TAG, "inflateWithoutRoot: inflaterVIew type="+inflateView.getClass().getSimpleName());
        mLiContainer.addView(inflateView);
    }

}
