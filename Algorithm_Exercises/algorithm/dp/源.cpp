#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>
#include"bitCompress.h"
#include"investment.h"
#include"LCS.h"
#include"maxSum.h"
#include<random>
#include<ctime>
std::vector<int> generateVector(long long n) {
	std::uniform_int_distribution<int> u(-10, 10);
	std::default_random_engine engine(time(0));
	std::vector<int> result;
	for (; n > 0; n--) {
		result.push_back(u(engine));
	}
	return result;
}

int main() {
	//InvestmentQuesttion();
	//std::string s1, s2;
	//std::cin >> s1 >> s2;
	//LCS(s1, s2);
	//std::vector<int> p{ 10,12,15,255,1,2,1,1,2,2,1,1};
	//compress(p);
	//auto v = generateVector(5000);
	//findMaxViolence(v);
	//findMaxByDivide(v);
	//findMaxByDp(v);

}