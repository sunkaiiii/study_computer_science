package com.example.sunkai.getwallpaer.ConenctService;

import android.text.TextUtils;

import com.example.sunkai.getwallpaer.Data.imageData;

import java.util.List;

/**
 * Created by sunkai on 2018/1/26.
 */

public class ConnectImageServiceBuilder {
    private int count=30;
    private int when=5;
    private final String url;
    private ConnectImageServiceBuilder(final String url){
        this.url=url;
    }
    public static ConnectImageServiceBuilder create(final String url)throws Exception{
        if(TextUtils.isEmpty(url))
            throw new Exception("url为空");
        return new ConnectImageServiceBuilder(url);
    }
    public ConnectImageServiceBuilder setCount(final int count){
        if(count<=0){
            this.count=30;
        }
        this.count=count;
        return this;
    }

    public ConnectImageServiceBuilder setWhen(final int when){
        if(when<0){
            this.when=0;
        }
        this.when=when;
        return this;
    }

    public List<imageData> post(){
        return ConenctImageService.GetImageData(url,this.count,this.when);
    }
}
