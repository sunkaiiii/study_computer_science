/*
某城市有一个火车站，有N节车厢从A方向驶入车站，按进展顺序编号为1~n，任务是判断是否能让它们按照某种特定的顺序进入另外一个车站，比如说出战顺序5,4,1,2,3是不可能的，但是5,4,3,2,1,是可以的。 
*/ 
#include<cstdio>
#include<stack>
using namespace std; 
int n;
const int MAXN = 1000 + 10;
int target[MAXN];
int main()
{
	while (scanf("%d", &n) == 1)
	{
		stack<int> s;
		int A = 1, B = 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", &target[i]);
		int ok = 1;
		while (B <= n)
		{
			if (A == target[B])
			{
				A++;
				B++;
			}
			else if (!s. empty() && s.top() == target[B])
			{
				s.pop();
				B++;
			}
			else if (A <= n)
			{
				s.push(A++);
			}
			else
			{
				ok = 0;
				break;
			}
		}
		printf("%s\n",ok?"yes":"no");
	}
    return 0;
}


