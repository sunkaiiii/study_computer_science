package com.example.sunkai.getwallpaer.ConenctService;

import com.example.sunkai.getwallpaer.Data.imageData;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

/*
 * Created by sunkai on 2018/1/26.
 */

public class ConenctImageService {


    public static List<imageData> GetImageData(String url, int count, int when) {
        Request request = new Request.Builder().url(url + "?count=" + count + "&when=" + when).build();
        OkHttpClient client = new OkHttpClient();
        try {
            Response response = client.newCall(request).execute();
            ResponseBody body = response.body();
            if (body != null) {
                Gson gson = new Gson();
                return gson.fromJson(body.string(), new TypeToken<List<imageData>>() {
                }.getType());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return Collections.emptyList();
    }
}
