
#include<iostream>
using namespace std;  
#define max(a,b) ((a)>(b)?(a):(b)) 
int main()
{
    int c,n;
    int a[300];
    cin>>c>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int take[300000];
    for(int i=0;i<n;i++)
    {
        for(int j=c;j>=a[i];j--)
        {
            take[j]=max(take[j],take[j-a[i]]+a[i]);
        }
    }
    cout<<c-take[c]<<endl;
}