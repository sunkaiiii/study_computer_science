#include<vector>
#include<string>
#include<iostream>
#include"LCS.h"
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
	auto findTrace = [](std::string s1, std::vector<std::vector<int>> trace, int i, int j) {
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
	findTrace(s1, trance, m - 1, n - 1);
	//最终时间复杂度O(N方)
}