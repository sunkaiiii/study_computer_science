package com.example.user.listviewasyncloading;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.AsyncTask;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;
import android.util.LruCache;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;

import com.android.volley.RequestQueue;
import com.android.volley.toolbox.ImageLoader;
import com.android.volley.toolbox.NetworkImageView;
import com.android.volley.toolbox.Volley;

import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by user on 2017/12/1.
 */

public class ImageAdapter extends ArrayAdapter<String> {
    //使用volley库的ImageLoader
    ImageLoader mImageLoader;

    public ImageAdapter(Context context,int resource,String[] objects){
        super(context,resource,objects);
        RequestQueue queue= Volley.newRequestQueue(context);
        mImageLoader=new ImageLoader(queue,new BitmapCache());
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        String url=getItem(position);
        View view;
        if(convertView==null){
            view=LayoutInflater.from(getContext()).inflate(R.layout.image_item,null);
        }else{
            view=convertView;
        }
        NetworkImageView image=(NetworkImageView)view.findViewById(R.id.image);
        image.setDefaultImageResId(R.drawable.th);
        image.setErrorImageResId(R.drawable.th);
        image.setImageUrl(url,mImageLoader);
        return view;
    }

    //使用LruCache来缓存图片
    public class BitmapCache implements ImageLoader.ImageCache{
        private LruCache<String,Bitmap> mCache;
        public BitmapCache(){
            //获得程序最大可用内存
            int maxMemory=(int)Runtime.getRuntime().maxMemory();
            int cacheSize=maxMemory/4;
            mCache=new LruCache<String,Bitmap>(cacheSize){
                @Override
                protected int sizeOf(String key, Bitmap bitmap) {
                    return bitmap.getRowBytes()*bitmap.getHeight();
                }
            };
        }

        @Override
        public Bitmap getBitmap(String url) {
            return mCache.get(url);
        }

        @Override
        public void putBitmap(String url, Bitmap bitmap) {
            mCache.put(url,bitmap);
        }
    }
}
