#include<iostream>
#include<vector>
#include<algorithm>

int findMax(int investments[4][6],std::vector<std::vector<int>> result,const  int i, const int j) {
	int max = result[i - 1][0] + investments[i][j];
	for (int i2 = 0; i2 <= j; i2++) {
		max = std::max(max, (result[i - 1][i2] + investments[i][j - i2]));
	}
	return max;
}

int main() {
	int investments[4][6]{ 0,11,12,13,14,15,0,0,5,10,15,20,0,2,10,30,32,40,0,20,21,22,23,24};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++){
			std::cout << investments[i][j] << " ";
		}
		std::cout<<std::endl;
	}
	int m;
	std::cin >> m;
	//µÝÍÆ·½³ÌFk(x)=max(fk(xk)+Fk-1(x-xk) k=2,3,...m
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
				result[i].push_back(findMax(investments,result, i, j));
			}
		}
	}
	std::cout << result[3][m];
}