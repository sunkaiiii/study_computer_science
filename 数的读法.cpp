/*
Tom教授正在给研究生讲授一门关于基因的课程，有一件事情让他颇为头疼：一条染色体上有成千上万个碱基对，它们从0开始编号，到几百万，几千万，甚至上亿。
　　比如说，在对学生讲解第1234567009号位置上的碱基时，光看着数字是很难准确的念出来的。
　　所以，他迫切地需要一个系统，然后当他输入12 3456 7009时，会给出相应的念法：
　　十二亿三千四百五十六万七千零九
　　用汉语拼音表示为
　　shi er yi san qian si bai wu shi liu wan qi qian ling jiu
　　这样他只需要照着念就可以了。
　　你的任务是帮他设计这样一个系统：给定一个阿拉伯数字串，你帮他按照中文读写的规范转为汉语拼音字串，相邻的两个音节用一个空格符格开。
　　注意必须严格按照规范，比如说“10010”读作“yi wan ling yi shi”而不是“yi wan ling shi”，“100000”读作“shi wan”而不是“yi shi wan”，“2000”读作“er qian”而不是“liang qian”。
*/
#include<iostream>
using namespace std;
int main()
{
	int a, c = 0;
	int b[100];
	cin >> a;
	char* ds[] = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu","liang" };
	while (a > 0)
	{
		b[c] = a % 10;
		a /= 10;
		c++;
	}
	int d;
	int e[100];
	int f = 0;
	for (d = c - 1; d >= 0; d--)
	{
		if (b[d] > 0 && d == 0)
			if (d == 0 && b[d + 1] == 0)
				cout << "ling " << ds[b[d]];
			else
				cout << ds[b[d]] << " ";
		else if ((d == 3 || d == 7 || d == 11) && b[d] > 0)
			cout << ds[b[d]] << " qian ";
		else if ((d == 2 || d == 6 || d == 10) && b[d] > 0)
			cout << ds[b[d]] << " bai ";
		else if ((d == 1 || d == 5 || d == 9) && b[d] > 0)
			if (c - 1 == d&&b[d] == 1)
				cout << "shi ";
			else if(b[d+1]==0)
				cout<<"ling "<<ds[b[d]]<<" shi ";
			else
				cout << ds[b[d]] << " shi ";
		else if (d == 4)
			cout << ds[b[d]] << " wan ";
		else if (d == 8)
			if (b[d] > 0)
				cout << ds[b[d]] << " yi ";
		else if (d == 0 && b[d] == 0)
				continue;
		else if (b[d] == 0 && d == 2)
			continue;
		else
			cout << ds[b[d]] << " ";
	}
	cout << endl;

}

