/*
***************************************
  Title: 蓝桥杯练习题—— 2n皇后问题
***************************************
  Date：2014/03/17
***************************************
  author：刘旭
***************************************
*/
#include<iostream>
using namespace std;
#define N   100
int wq[N];		   //whitequeen,黑皇后位置
int bq[N];		   //blackqueen,白皇后位置
int cb[N][N];		//chessboard,棋盘
int num;			 //皇后数目
int count = 0;	   //不同放置情况计数
int bqueen(int pos)  //白色皇后放置
{
  int i;
  for(i = 0; i < pos -1; i++)
  {
    int judge = bq[i] - bq[pos-1];
    if(0 == judge || judge == pos - 1 - i || -judge == pos - 1 - i)
      return 0;
  }
  if(pos == num)
  {
    count++;
    return 0;
  }

  for(int i = 0; i < num; i++)
  {
    if(i != wq[pos] && cb[pos][i])
    {
      bq[pos] = i;
      bqueen(pos+1);
    }
  }
}
int wqueen(int pos) //黑色皇后放置
{
  int i;
  for(i = 0; i < pos -1; i++)
  {
    int judge = wq[i] - wq[pos-1];
    if(0 == judge || judge == pos - 1 - i || -judge == pos - 1 - i)
      return 0;
  }
  if(pos == num)
  {
    bqueen(0);
    return 0;
  }

  for(int i = 0; i < num; i++)
  {
   if(cb[pos][i])
    {
      wq[pos] = i;
      wqueen(pos+1);
    }

  }
}
int main()
{
  cin>>num;
  for(int i =0; i < num; i++)
    for(int j = 0; j < num; j++)
      cin>>cb[i][j];
  wqueen(0);
  cout<<count;
  return 0;
}
