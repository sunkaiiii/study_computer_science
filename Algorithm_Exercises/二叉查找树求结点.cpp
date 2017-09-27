/*
满二叉树的深度K,2^k-1个节点,节点值1~2^k-1
,给出k和任意3个节点的值,输出包含3个节点，且最小子树的根节点
*/
#include <iostream>
#include <algorithm>
using namespace std;

int mypow(int x,int n){
  if(n==0) return 1;
  if(n==1) return x;
  int tem = mypow(x,n/2);
  if(n%2==1){
    return tem*tem*x;
  }
  return tem*tem;
}

int main(){
  int k;
  int a[3];
  cin>>k>>a[0]>>a[1]>>a[2];
  sort(a,a+3);
  int root=2;
  for(int i=1;i<k;i++)
  {
    root=root*2;
  }
  root/=2;
  while(true){
    if(a[0] <= root && a[2]>=root) {
      cout<<root<<endl;
      return  0;
    }
    else if(a[2]<root){
        root /= 2;
    }
    else if(a[0]>root){
        root += root/2;
    }
  }
}
