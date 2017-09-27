//输入M行N列的字符矩阵，统计@组成多少个连续快，如果两个@相邻，就算他们属于一个连续快
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100 + 5;
char pic[maxn][maxn];
int m, n, idx[maxn][maxn];
void dfs(int r, int c, int id)
{
	if (r < 0 || r == m || c < 0 || c >= n)
		return;//出界的格子
	if (idx[r][c] > 0 || pic[r][c] != '@')
		return;//不是@或者表示已经访问过的格子
	idx[r][c] = id;
	for (int dr = -1; dr <= 1; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
			if (dr != 0 || dc != 0)
				dfs(r + dr, c + dc, id);
	}
}
int main()
{
	while (scanf("%d%d", &m, &n) == 2 && m&&n)
	{
		for (int i = 0; i < m; i++)
			scanf("%s", pic[i]);
		memset(idx, 0, sizeof(idx));
		int cnt = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (idx[i][j] == 0 && pic[i][j] == '@')
				{
					dfs(i, j, ++cnt);
				}
		printf("%d\n", cnt);
	}
}