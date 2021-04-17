package com.example.sunkai.a0604test;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Main6Activity extends AppCompatActivity {
    private ThreadLocal<Boolean> mBooleanThreadLocal=new ThreadLocal<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main6);
        mBooleanThreadLocal.set(true);
        Log.d("test6","ThreadLocal:"+mBooleanThreadLocal.get());
        //将会在log里面输出true，false，null
        new Thread("thread1"){
            @Override
            public void run() {
                mBooleanThreadLocal.set(false);
                Log.d("test6","Thread1 ThreadLocal:"+mBooleanThreadLocal.get());
            }
        }.start();
        new Thread("thread2"){
            @Override
            public void run() {
                Log.d("test6","Thread2 ThreadLocal:"+mBooleanThreadLocal.get());
            }
        }.start();

        //观察AsyncTask的实行情况
        new MyAsyncTask("task1").execute("");
        new MyAsyncTask("task2").execute("");
        new MyAsyncTask("task3").execute("");
        new MyAsyncTask("task4").execute("");
        new MyAsyncTask("task5").execute("");

        //AsyncTask并实行的情况
        new MyAsyncTask("task6").executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,"");
        new MyAsyncTask("task7").executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,"");
        new MyAsyncTask("task8").executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,"");
        new MyAsyncTask("task9").executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,"");
        new MyAsyncTask("task10").executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,"");

    }

    private class  MyAsyncTask extends AsyncTask<String,Integer,String>{
        private String mName="AsyncTask";

        public MyAsyncTask(String name){
            super();
            mName=name;
        }

        @Override
        protected String doInBackground(String... strings) {
            try{
                Thread.sleep(3000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
            return mName;
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            SimpleDateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            Log.e("test7",s+"finish at "+df.format(new Date()));
        }
    }
}
