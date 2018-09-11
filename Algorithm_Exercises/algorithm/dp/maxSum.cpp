#include<vector>
#include<iostream>
#include<algorithm>

//O(n3)的暴力解法
void findMaxViolence(std::vector<int> v) {
	int maxSum = 0;
	int first;
	int last;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			int tempSum = 0;
			for (auto k = i; k <= j; k++) {
				tempSum += v[k];
			}
			if (maxSum < tempSum) {
				maxSum = tempSum;
				first = i;
				last = j;
			}
		}
	}
	std::cout << maxSum << std::endl;
}


//O(nlogn)的分治解法
int findMaxDivide(const std::vector<int> &v,const int left,const int right) {
	if (left == right) {
		return std::max(v[left], 0); //如果是负值，干脆就不加进去
	}
	int mid = (left + right) / 2;
	int leftSum = findMaxDivide(v, left, mid);
	int rightSum = findMaxDivide(v, mid + 1, right);
	int s1 = 0;
	int s2 = 0;
	int s1temp =0;
	for (int i = mid; i >= left; i--) {
		s1temp += v[i];
		s1 = std::max(s1temp, s1);
	}
	int s2temp = 0;
	for (int i = mid + 1; i < right; i++) {
		s2temp += v[i];
		s2=std::max(s2temp,s2);
	}
	int sum = s1 + s2;
	if (leftSum > sum){
		sum = leftSum;
	}
	if (rightSum > sum) {
		sum = rightSum;
	}
	return sum;
}

void findMaxByDivide(std::vector<int> v) {
	std::cout << findMaxDivide(v, 0, v.size()-1)<<std::endl;
}

//O(n)的动态规划解法
void findMaxByDp(std::vector<int> v) {
	int  sum = 0;
	int temp = 0;
	for (int i = 0; i < v.size(); i++) {
		if (temp > 0) {
			temp += v[i];
		}
		else {
			temp = v[i];
		}
		if (temp > sum) {
			sum = temp;
		}
	}
	std::cout << sum << std::endl;
}