#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

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
}

int main() {
	//InvestmentQuesttion();
	std::string s1, s2;
	std::cin >> s1 >> s2;
	LCS(s1, s2);
}