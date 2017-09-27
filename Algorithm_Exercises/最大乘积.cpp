/*
问题描述 

　　今年是国际数学联盟确定的“2000——世界数学年”，又恰逢我国著名数学家华罗庚先生诞辰90周年。在华罗庚先生的家乡江苏金坛，组织了一场别开生面的数学智力竞赛的活动，你的一个好朋友XZ也有幸得以参加。活动中，主持人给所有参加活动的选手出了这样一道题目：

　　设有一个长度为N的数字串，要求选手使用K个乘号将它分成K+1个部分，找出一种分法，使得这K+1个部分的乘积能够为最大。

　　同时，为了帮助选手能够正确理解题意，主持人还举了如下的一个例子：

　　有一个数字串：312， 当N=3，K=1时会有以下两种分法：

　　3*12=36
　　31*2=62

　　这时，符合题目要求的结果是：31*2=62

　　现在，请你帮助你的好朋友XZ设计一个程序，求得正确的答案。

输入格式 

　　程序的输入共有两行：
　　第一行共有2个自然数N，K（6≤N≤40，1≤K≤6）
　　第二行是一个长度为N的数字串。


输出格式 

　　输出所求得的最大乘积（一个自然数）。

　　样例输入

　　4 2
　　1231
样例输出
62
*/
#include<iostream>
#include<cstring>
using namespace std;  
int change(string a)  
{  
    int ans=a[0]-'0';  
    int len=a.length();  
    for(int i=1;i<len;i++)  
   {  
       ans=ans*10+a[i]-'0';  
    }  
    return ans;  
}  
int main()  
{  
    int m,n;  
    cin>>m>>n;  
    string s;  
    cin>>s;  
    long long ans[45][7];  
    memset(ans,0,sizeof(ans));  
    for(int i=1;i<=m;i++)  
    {
         ans[i-1][0]=change(s.substr(0,i));
         //cout<<ans[i-1][0]<<",";    
    }   
    for(int i=0;i<m;i++)   
    {  
       // cout<<i<<":"<<endl;
        int t=min(i,n);  
        for(int j=1;j<=t;j++)  
        {  
            for(int k=0;k<i;k++)  
            {  
                long long tt=change(s.substr(k+1,i-k));  
                ans[i][j]=max(ans[i][j],ans[k][j-1]*tt);
                //cout<<ans[i][j]<<",";  
            }  
        } 
        //cout<<endl; 
    }  
    cout<<ans[m-1][n];  
}   
