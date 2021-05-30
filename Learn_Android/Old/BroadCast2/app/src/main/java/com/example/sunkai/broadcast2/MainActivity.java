package com.example.sunkai.broadcast2;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private IntentFilter intentFilter,intentFilter2;
    private NetworkChangeRecevier networkChangeReceiver;

    private LocalBroadcastManager localBroadcastManager;
    private LocalRecevier localRecevier;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        intentFilter=new IntentFilter();
        intentFilter.addAction("android.net.conn.CONNECTIVITY_CHANGE"); //监控网络变化
        networkChangeReceiver=new NetworkChangeRecevier();
        registerReceiver(networkChangeReceiver,intentFilter);

        intentFilter2=new IntentFilter();
        intentFilter2.addAction("com.example.sunkai.broadcast2.LOCAL_BROADCAST");
        localRecevier=new LocalRecevier();
        localBroadcastManager=LocalBroadcastManager.getInstance(this); //获取实例
        Button button=findViewById(R.id.button);
        button.setOnClickListener((v)->{
            Intent intent=new Intent("com.example.sunkai.broadcast2.LOCAL_BROADCAST");
            localBroadcastManager.sendBroadcast(intent); //发送本地广播
        });
        localBroadcastManager.registerReceiver(localRecevier,intentFilter2);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(networkChangeReceiver);
        localBroadcastManager.unregisterReceiver(localRecevier);
    }

    public class NetworkChangeRecevier extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            ConnectivityManager connectivityManager=(ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo networkInfo=connectivityManager.getActiveNetworkInfo();
            if(networkInfo!=null&&networkInfo.isAvailable()){
                Toast.makeText(context,"network is available",Toast.LENGTH_SHORT).show();
            }else{
                Toast.makeText(context,"network is unavailable",Toast.LENGTH_SHORT).show();
            }
        }
    }

    public class LocalRecevier extends BroadcastReceiver{
        @Override
        public void onReceive(Context context, Intent intent) {
            Toast.makeText(context,"received local broadcast",Toast.LENGTH_SHORT).show();
        }
    }

}
