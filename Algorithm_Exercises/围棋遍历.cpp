/*
[编程|14分] 围棋遍历
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 32768K，其他语言 65536K
题目描述
函数calc计算围棋中位置(x,y)处连成一片的棋子个数。所谓连成一片，即沿着棋盘横竖线往任意方向遍历，遍历过程允许转弯，不允许走斜线，中间未出现对方棋子或空子。

enum color {
    NONE, WHITE, BLACK,         // 棋子颜色，NONE表示未落子
};
struct weiqi {
    enum color board[19][19];   // 棋盘上每个位置的落子
};
int calc(struct weiqi *wq, int x, int y)
{
}

输入描述:
第1-19行数据是棋盘上棋子的颜色数据。0表示未落子，1表示白子，2表示黑子。 第1行最左边位置的坐标是(0,0)，第1行第2列的坐标是(1,0)，第2行第1列的坐标是(0,1)，依此类推。 第20行数据是起始坐标(x,y)
输出描述:
与坐标(X,Y)连成一片的棋子数目
示例1
输入

0000000000000000000
0000011000000000000
0000001111000000000
0000001021000000000
0000001010100000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
0000000000000000000
5,1
输出

9
*/
#include <stdio.h>
#include <string.h>
#include<queue>
#include<map>

enum color {
    NONE, WHITE, BLACK,         //棋子颜色，NONE表示未落子
};
struct weiqi {
    enum color board[19][19];   //棋盘上每个位置的落子
};

int calc(struct weiqi *wq, int x, int y)
{
  int a[20][20];
  for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
      a[i][j]=0;
  color c=wq->board[y][x];
  if(c==NONE)
    return 0;
  int result=1;
  std::queue<std::pair<int,int>> q;
  if(y-1>=0&&wq->board[y-1][x]==c)
    q.push(std::pair<int,int>(y-1,x));
  if(y+1<19&&wq->board[y+1][x]==c)
    q.push(std::pair<int,int>(y+1,x));
  if(x+1<19&&wq->board[y][x+1]==c)
    q.push(std::pair<int,int>(y,x+1));
  if(x-1>=0&&wq->board[y][x-1]==c)
    q.push(std::pair<int,int>(y,x-1));
  a[y][x]=1;
  while(!q.empty())
  {
    auto p=q.front();
    q.pop();
    int y2=p.first;
    int x2=p.second;
    // printf("%d,%d\n",y2,x2 );
    if(a[y2][x2]==0)
    {
      a[y2][x2]=1;
      result++;
    }
    else
    {
      continue;
    }
    // printf("%d,%d\n",y2,x2 );
    if(y2-1>=0&&wq->board[y2-1][x2]==c)
      q.push(std::pair<int,int>(y2-1,x2));
    if(y2+1<19&&wq->board[y2+1][x2]==c)
      q.push(std::pair<int,int>(y2+1,x2));
    if(x2+1<19&&wq->board[y2][x2+1]==c)
      q.push(std::pair<int,int>(y2,x2+1));
    if(x2-1>=0&&wq->board[y2][x2-1]==c)
      q.push(std::pair<int,int>(y2,x2-1));
  }
  return result;
}
int input(struct weiqi *wq, int *x, int *y)
{
    int row, col;
    int ret;
    char buf[80];

    for (row = 0; row < 19; ++row) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return -1;
        if (strlen(buf) < 19)
            return -1;
        for (col = 0; col < 19; ++col) {
            switch (buf[col]) {
            case '0':
                wq->board[row][col] = NONE;
                break;
            case '1':
                wq->board[row][col] = WHITE;
                break;
            case '2':
                wq->board[row][col] = BLACK;
                break;
            default:
                return -1;
            }
        }
    }
    ret = fscanf(stdin, "%d,%d\n", x, y);
    if (ret != 2)
        return -1;
    for (row = 0 ; row < 19; ++row) {
        for (col = 0; col < 19; ++col) {
            fprintf(stderr, "%d ", wq->board[row][col]);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "x = %d, y = %d\n", *x, *y);
    return 0;
}

int main()
{
    struct weiqi wq;
    int x = 0, y = 0;
    int cnt;

    memset(&wq, 0, sizeof(wq));
    if (input(&wq, &x, &y) < 0) {
        fprintf(stderr, "error!\n");
        return 1;
    }
    cnt = calc(&wq, x, y);

    printf("%d\n", cnt);
    return 0;
}
