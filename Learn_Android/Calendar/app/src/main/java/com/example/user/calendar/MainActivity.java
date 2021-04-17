package com.example.user.calendar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.format.DateFormat;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //获取Calendar实例
        Calendar calendar=Calendar.getInstance();
        System.out.println(calendar.get(Calendar.YEAR)+"年"
                +calendar.get(Calendar.MONTH)+"月"
                +calendar.get(Calendar.DAY_OF_MONTH)+"日"
                +calendar.get(Calendar.HOUR_OF_DAY)+"时"
                +calendar.get(Calendar.MINUTE)+"分"
                +calendar.get(Calendar.SECOND)+"秒 \n星期"
                +calendar.get(Calendar.DAY_OF_WEEK)+"是今年第"
                +calendar.get(Calendar.WEEK_OF_YEAR)+"周"
        );
        System.out.println(DateFormat.format("yyyy-MM-dd kk:mm:ss",calendar.getTime()));

        //将日期转换成毫秒
        try{
            Date calendarDate=calendar.getTime();

            String time=DateFormat.format("yyyy-MM-dd kk:mm:ss",calendarDate).toString();

            System.out.println("DateFormat格式化后String值："+time);

            SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd kk:mm:ss");

            Date date=format.parse(time);

            System.out.println("date.getTIme:"+date.getTime());

            System.out.println("format.parse()"+format.parse("2014-08-29 15:56:00"));
        }catch (ParseException e){
            e.printStackTrace();
        }
    }
}
