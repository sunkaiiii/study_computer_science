package com.example.user.packagemanager;

import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;


/**
 * Created by user on 2017/11/29.
 */

public class listViewAdapter extends BaseAdapter {
    Context context;
    LayoutInflater inflater;
    List<ResolveInfo> infos;
    PackageManager pm;

    public listViewAdapter(Context context, List<ResolveInfo> infos, PackageManager pm){
        this.context=context;
        inflater= LayoutInflater.from(context);
        this.infos=infos;
        this.pm=pm;
        Collections.sort(infos,new PriceComparator());
    }

    //给传递进来的应用名称做排序

    class PriceComparator implements Comparator{
        @Override
        public int compare(Object o, Object t1) {
            ResolveInfo r1=(ResolveInfo)o;
            ResolveInfo r2=(ResolveInfo)t1;
            return r1.loadLabel(pm).toString().compareTo(r2.loadLabel(pm).toString());
        }
    }

    @Override
    public Object getItem(int i) {
        return infos.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public int getCount() {
        return infos.size();
    }

    @Override
    public View getView(int i, View convertView, ViewGroup viewGroup) {
        Holder holder;
        if(convertView==null){
            convertView=inflater.inflate(R.layout.listview_item,null);
            holder=new Holder();
            holder.appLabel=(TextView)convertView.findViewById(R.id.ImagetextView);
            holder.imageView=(ImageView)convertView.findViewById(R.id.imageView);
            holder.appName=(TextView)convertView.findViewById(R.id.application_content);

            convertView.setTag(holder);
        }
        else{
            holder=(Holder)convertView.getTag();
        }
        holder.appLabel.setText(infos.get(i).loadLabel(pm).toString());
        holder.appName.setText(infos.get(i).activityInfo.name);
        holder.imageView.setImageDrawable(infos.get(i).loadIcon(pm));
        return convertView;
    }

    class Holder{
        TextView appLabel,appName;
        ImageView imageView;
    }
}
