package com.example.user.xgnotification;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import com.tencent.android.tpush.XGIOperateCallback;
import com.tencent.android.tpush.XGPushConfig;
import com.tencent.android.tpush.XGPushManager;

public class MainActivity extends AppCompatActivity {

    Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        button=(Button)findViewById(R.id.sned_btn);
        XGPushConfig.enableDebug(this,true);
        XGPushManager.registerPush(this, new XGIOperateCallback() {
            @Override
            public void onSuccess(Object o, int i) {
                    Log.d("TPush","注册成功，设备token为"+o);
                }

            @Override
            public void onFail(Object o, int i, String s) {
                    Log.d("Tpush","注册失败，错误码"+i+"，错误信息"+s);
            }
        });



    }
}
