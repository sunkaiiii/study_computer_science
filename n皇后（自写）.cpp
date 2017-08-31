#include<iostream>
#include<cstring>
int n;
int a[10002][10002];
void f(int count)
{
  if(count==n)
  {
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
        std::cout<<a[i][j]<<" ";
      }
      std::cout<<std::endl;
    }
    std::cout<<std::endl;
  }
  else
  {
    for(int i=0;i<n;i++)
    {
      if(count==0)
      {
        a[count][i]=1;
        f(count+1);
        a[count][i]=0;
      }
      else
      {
        int ok=1;
        for(int d=count-1;d>=0;d--)
        {
          if(a[d][i]==1)
          {
            ok=0;
            break;
          }
        }
        int d=count-1;
        for(int j=i-1;j>=0;j--)
        {
          if(d<0)
          {
            break;
          }
          if(a[d][j]==1)
          {
            ok=0;
            break;
          }
          d--;
        }
        d=count-1;
        for(int j=i+1;j<n;j++)
        {
          if(d<0)
          {
            break;
          }
          if(a[d][j]==1)
          {
            ok=0;
            break;
          }
          d--;
        }
        if(ok)
        {
          a[count][i]=1;
          f(count+1);
          a[count][i]=0;
        }
      }
    }
  }
}
int main()
{
  std::cin>>n;
  f(0);
}
