#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>

int findMax(int investments[4][6],std::vector<std::vector<int>> result,const  int i, const int j) {
	int max = result[i - 1][0] + investments[i][j];
	for (int i2 = 0; i2 <= j; i2++) {
		max = std::max(max, (result[i - 1][i2] + investments[i][j - i2]));
	}
	return max;
}

void InvestmentQuesttion() {
	int investments[4][6]{ 0,11,12,13,14,15,0,0,5,10,15,20,0,2,10,30,32,40,0,20,21,22,23,24 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			std::cout << investments[i][j] << " ";
		}
		std::cout << std::endl;
	}
	int m;
	std::cin >> m;
	//递推方程Fk(x)=max(fk(xk)+Fk-1(x-xk) k=2,3,...m
	//F1(x)=f1(x) F(0)=0 k=1,2...m
	std::vector<std::vector<int>> result(4);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= m; j++) {
			if (j == 6) {
				break;
			}
			if (i == 0) {
				result[i].push_back(investments[i][j]);
			}
			else {
				result[i].push_back(findMax(investments, result, i, j));
			}
		}
	}
	//投资项目数量为N，金钱为M，根据代码，可以轻易的看出来时间复杂度为O(nm平方)
	std::cout << result[3][m];
}

void LCS(const std::string s1, const std::string s2) {
	static const int UPPER_LEFT = 0;
	static const int UP = 1;
	static const int LEFT = 2;
	const int m = s1.length();
	const int n = s2.length();
	std::vector<std::vector<int>> c(m);
	for (int i = 0; i < m; i++) {
		std::vector<int> temp(n);
		c[i] = temp;
	}
	auto trance = c;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (s1[i] == s2[j]) { //s1[i]与s2[j]被选入公共子序列
				trance[i][j] = UPPER_LEFT;
				if (i > 0 && j > 0) {
					c[i][j] = c[i - 1][j - 1] + 1;
				}
				else {
					c[i][j] = 1;
				}
			}
			else {
				if (i == 0 || j == 0) {
					c[i][j] = 0;
					continue;
				}
				if (c[i - 1][j] >= c[i][j - 1]) {
					c[i][j] = c[i - 1][j];
					trance[i][j] = UP;
				}
				else {
					trance[i][j] = LEFT;
					c[i][j] = c[i][j - 1];
				}
			}
		}
	}
	std::cout << c[m - 1][n - 1];
	auto findTrace = [](std::string s1,std::vector<std::vector<int>> trace,int i,int j) {
		static void(*inner)(std::string, std::vector<std::vector<int>>, int, int) = [](std::string s1, std::vector<std::vector<int>> trace, int i, int j) {
			if (i == 0 || j == 0) {
				return; //序列为空
			}
			if (trace[i][j] == UPPER_LEFT) {
				std::cout << s1[i];
				inner(s1, trace, i - 1, j - 1);
			}
			else if (trace[i][j] == UP) {
				inner(s1, trace, i - 1, j);
			}
			else {
				inner(s1, trace, i, j - 1);
			}
		};
		inner(s1, trace, i, j);
	};
	findTrace(s1,trance,m-1,n-1);
	//最终时间复杂度O(N方)
}

void traceBack(int n, std::vector<int> l);
int length(int i);
void compress(std::vector<int> origin) {
	const static int maxLength = 256;
	const static int header = 11;
	std::vector<int> s;
	std::vector<int> b;
	std::vector<int> l;
	s.push_back(0);
	b.push_back(0);
	l.push_back(0);
	std::vector<int> p{ 0 };
	for (int value : origin) {
		p.push_back(value);
	}
	for (int i = 1; i < p.size(); i++){
		b.push_back(length(p[i]));
		int bmax = b[i];
		s.push_back(s[i - 1] + bmax);
		l.push_back(1);
		for (int j = 2; j <= std::min(i, maxLength);j++) {
			if (bmax < b[i - j + 1]) {
				bmax = b[i - j + 1];
			}
			if (s[i] > s[i - j] + j * bmax) {
				s[i] = s[i - j] + j * bmax;
				l[i] = j;
			}
		}
		s[i] +=  header;
	}
	for (int count : s) {
		std::cout << count << " ";
	}
	std::cout << std::endl;
	std::cout << s[p.size() - 1]<<std::endl;
	traceBack(p.size()-1,l);
}

int length(int i) {
	int count = 0;
	while (i > 0) {
		i = i >> 1;
		count++;
	}
	return count;
}

void traceBack(int n, std::vector<int> l) {
	std::vector<int> c;
	while (n != 0) {
		c.push_back(l[n]);
		n -= l[n];
	}
	for (int i : c) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}


int main() {
	//InvestmentQuesttion();
	//std::string s1, s2;
	//std::cin >> s1 >> s2;
	//LCS(s1, s2);
	std::vector<int> p{ 10,12,15,255,1,2};
	compress(p);
}