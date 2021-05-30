package com.example.sunkai.httpurlconnection;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MainActivity extends AppCompatActivity {
    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button=findViewById(R.id.button);
        textView=findViewById(R.id.textview);
        button.setOnClickListener((v)->{
            httpGetTest();
        });
    }
    private void httpGetTest(){
        new Thread(()->{
            HttpsURLConnection connection=null;
            BufferedReader reader=null;
            try {
                URL url = new URL("https://www.baidu.com");
                connection=(HttpsURLConnection)url.openConnection();
                connection.setRequestMethod("GET");
                connection.setConnectTimeout(8000);
                connection.setReadTimeout(8000);
                InputStream in=connection.getInputStream();
                //下面对获取到的输入流进行读取
                reader=new BufferedReader(new InputStreamReader(in));
                StringBuilder response=new StringBuilder();
                String line;
                while((line=reader.readLine())!=null){
                    response.append(line);
                }
                showResponse(response.toString());
            }catch (MalformedURLException e){
                e.printStackTrace();
            }catch (IOException e){
                e.printStackTrace();
            }finally {
                if(reader!=null){
                    try{
                        reader.close();
                    }catch (IOException e){
                        e.printStackTrace();
                    }
                }
                if(connection!=null){
                    connection.disconnect();
                }
            }
        }).start();
    }

    private void showResponse(final String response){
        runOnUiThread(() -> textView.setText(response));
    }
}
