package com.example.sunkai.loadimage;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.util.LruCache;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private Button buttonGet,buttonSet;
    private ImageView imageView;
    private LruCache<Integer,Bitmap> mMemoryCache;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        int maxMemory=(int)(Runtime.getRuntime().maxMemory()/1024);
        int cacheSize=maxMemory/8;
        //申请一个cache，大小为可用内存值的1/8
        mMemoryCache=new LruCache<Integer,Bitmap>(cacheSize){
            @Override
            protected int sizeOf(Integer key, Bitmap bitmap) {
                return bitmap.getByteCount()/1024;
            }
        };
        buttonGet=(Button)findViewById(R.id.show_option_btn);
        buttonSet=(Button)findViewById(R.id.set_img_btn);
        imageView=(ImageView)findViewById(R.id.show_img);
        buttonGet.setOnClickListener((view -> getOption()));
        buttonSet.setOnClickListener((view -> setImage()));
    }

    public void addBitmapToMemoryCache(int key,Bitmap bitmap){
        if(getBitmapFrommemoryCache(key)==null)
            mMemoryCache.put(key,bitmap);
    }

    public Bitmap getBitmapFrommemoryCache(int key){
        return mMemoryCache.get(key);
    }

    private void setImage(){
        ViewGroup.LayoutParams layoutParams=imageView.getLayoutParams();
        Bitmap bitmap=decodeSampleBitmapFromResource(getResources(),R.drawable.test_image,layoutParams.width,layoutParams.height);
        Log.d(TAG, "setImage: height:"+layoutParams.height+",width:"+layoutParams.width);
        imageView.setImageBitmap(bitmap);
    }


    private void getOption(){
        //inJustDecodeBound属性为true可以让解析方法禁止为bitmap分配内存
        //并且返回值也不再是一个bitmap对象
        //虽然返回null了，但是会让BitmapFactory.Options的outWidth和outHeight和outMimeType属性赋值
        BitmapFactory.Options options=new BitmapFactory.Options();
        options.inJustDecodeBounds=true;
        BitmapFactory.decodeResource(getResources(),R.drawable.test_image,options);
        int imageHeight=options.outHeight;
        int imageWidth=options.outWidth;
        String imageType=options.outMimeType;
        Log.d(TAG, "imageHeight:"+imageHeight+" imageWidth:"+imageWidth+" imageType:"+imageType);
    }

    private static int calculateInSampleSize(BitmapFactory.Options options,int reqWidth,int reqHeight){
        //原图片的高度和宽度
        final int height=options.outHeight;
        final int width=options.outWidth;
        int inSampleSize=1;
        if(height>reqHeight||width>reqWidth){
            //计算出实际宽高和目标高的比率
            final int heightRatio=Math.round((float)height/(float)reqHeight);
            final int widthRatio=Math.round((float)width/(float)reqWidth);
            //选择宽和高中最小的比率作为inSampleSize的值，这样可以保证最终图片的宽和高
            //一定会大于目标的款和高
            inSampleSize=heightRatio<widthRatio?heightRatio:widthRatio;
        }
        return inSampleSize;
    }

    private Bitmap decodeSampleBitmapFromResource(Resources res,int resid,int reqWidth,int reqHeight){
        Bitmap bitmap=getBitmapFrommemoryCache(resid);
        if(bitmap!=null)
            return bitmap;
        //第一次解析将inJustDecodeBounds设置为true，来获取图片大小
        final BitmapFactory.Options options=new BitmapFactory.Options();
        options.inJustDecodeBounds=true;
        BitmapFactory.decodeResource(res,resid,options);
        //调用上面的方法来计算inSampleSize的值
        options.inSampleSize=calculateInSampleSize(options,reqWidth,reqHeight);
        //使用获取到的inSampleSize再次解析图片
        options.inJustDecodeBounds=false;
        Log.d(TAG, "decodeSampleBitmapFromResource: "+options.inSampleSize);
        bitmap= BitmapFactory.decodeResource(res,resid,options);
        addBitmapToMemoryCache(resid,bitmap);
        return bitmap;
    }
}
