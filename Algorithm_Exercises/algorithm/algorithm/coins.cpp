#include<iostream>
#include<vector>
#include<assert.h>
#include<random>
#include<time.h>
std::vector<int> generateRandomNum(const int n) {
	std::vector<int> coins;
	int badNumber = n / 2;
	int goodNumber = n - n/2;
	if (goodNumber == badNumber) {
		goodNumber += 1;
		badNumber -= 1;
	}
	assert(goodNumber > badNumber);
	std::uniform_int_distribution<int> u(0,1);
	std::default_random_engine e(time(0));
	for (; badNumber > 0 && goodNumber > 0;) {
		auto number = u(e);
		if (number % 2 == 0) {
			goodNumber--;
		}
		else {
			badNumber--;
		}
		coins.push_back(number);
	}
	while (badNumber > 0) {
		coins.push_back(1);
		badNumber--;
	}
	while (goodNumber > 0) {
		coins.push_back(0);
		goodNumber--;
	}
	return coins;
}

int check1(const std::vector<int> & coins) {
	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e(time(0));
	for (auto i = 0; i < coins.size(); i++) {
		auto number=0;
		for (auto j = 0; j < coins.size(); j++) {
			if(i==j){
				continue;
			}
			if (coins[j] == 0) {
				if (coins[i] == 1) {
					number++;
				}
			}
			else {
				number += u(e);
			}
		}
		if (number >= coins.size() / 2) {
			return i;
		}
	}
	return -1;
}

int check2(const std::vector<int> &coins) {
	int n = coins.size();
	std::vector<int> tempResult = coins;
	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e(time(0));
	while (n > 3) {
		std::vector<int> loopVector;
		for (auto i = 0; i < tempResult.size()-1; i+=2) {
			int aResult;
			int bResult;
			if (tempResult[i] == 0) {
				aResult = tempResult[i + 1];
			}
			else {
				aResult = u(e);
			}
			if (tempResult[i+1] == 0) {
				bResult = tempResult[i];
			}
			else {
				bResult = u(e);
			}
			if (aResult == 1 && bResult == 1) {
				int stay = u(e);
				if (stay == 0) {
					loopVector.push_back(tempResult[i]);
				}
				else {
					loopVector.push_back(tempResult[i + 1]);
				}
				n -= 1;
			}
			else {
				n -= 2;
			}
		}
		tempResult = loopVector;
	}
	switch (n)
	{
	case 3:
		int aResult;
		int bResult;
		if (tempResult[0] == 0) {
			aResult = tempResult[1];
		}
		else {
			aResult = u(e);
		}
		if (tempResult[1] == 0) {
			bResult = tempResult[0];
		}
		else {
			bResult = u(e);
		}
		if (aResult == 1 && bResult == 1) {
			return tempResult[u(e)];
		}
		else {
			return tempResult[2];
		}
		break;
	case 2:
		return tempResult[u(e)];
		break;
	default:
		break;
	}
}

int main() {
	auto coins = generateRandomNum(500);
	for (const int number : coins) {
		printf("%d,", number);
	}
	std::cout << std::endl << std::endl << std::endl;
	std::cout << check1(coins) << std::endl;
	std::cout << check2(coins) << std::endl;
}