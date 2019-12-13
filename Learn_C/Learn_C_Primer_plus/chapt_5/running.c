/* running.c -- An useful example for this chapter*/
#include<stdio.h>
const int S_PER_M=60;
const int S_PER_H=3600;
const double M_PER_K=0.62137;

int main(void)
{
    double distk,distm; //跑过的距离
    double rate; //平均速度
    int min,sec; //跑步用时
    int time; //跑步用时（以秒）
    double mtime; //跑1英里需要的时间
    int mmin,mesc; //跑1英里需要的时间（以分钟和秒）

    printf("This program converts your time for a metric race\n");
    printf("to a time for running a mile and to your average\n");
    printf("speed in miles per hour\n");
    printf("Please enter, in kilometers, the distance run.\n");
    scanf("%lf",&distk);
    printf("Next enter the time in minutes and seconds\n");
    printf("Begin by entering the minutes\n");
    scanf("%d",&min);
    printf("now enter the seconds\n");
    scanf("%d",&sec);

    time=S_PER_M*min+sec; //把时间转换成秒
    distm=M_PER_K*distk; //把公里转换成英里
    rate=distm/time*S_PER_H; //速度
    mtime=(double)mtime/S_PER_M; 
    mmin=(int)mtime/S_PER_M; //求出分钟
    mesc=(int)mtime%S_PER_M; //求出剩余的秒数

    printf("You ran %1.2f km (%1.2f miles) in %d min, %d sec.\n",distk,distm,min,sec);
    printf("That pace corresponds to running a mile in %d min,",mmin);
    printf("%d sec.\nYour average speed was %1.2f mph\n",mesc,rate);
    return 0;
}