/*问题描述
　　有形如：ax3+bx2+cx+d=0 这样的一个一元三次方程。给出该方程中各项的系数(a，b，c，d 均为实数)，并约定该方程存在三个不同实根(根的范围在-100至100之间)，且根与根之差的绝对值>=1。要求三个实根。。
输入格式
　　四个实数：a，b，c，d
输出格式
　　由小到大依次在同一行输出这三个实根(根与根之间留有空格)，并精确到小数点后2位
样例输入
1 -5 -4 20
样例输出
-2.00 2.00 5.00
数据规模和约定
　　|a|，|b|，|c|，|d|<=10
*/
#include<iostream>
#include <iomanip>
using namespace std;
double a,b,c,d;
double f(double x)
{
    return x*x*x+b*1.00/a*x*x+c*1.00/a*x+d*1.00/a;
}
int main()
{
    cin>>a>>b>>c>>d;
    for(int x=-10000;x<=10000;x++)
    {
        double x1=(x-0.05)*1.00/100,x2=(x+0.05)*1.00/100;
        if(f(x1)*f(x2)<0)
            printf("%.2f ",x*1.00/100);
    }
    cout<<endl;
}
