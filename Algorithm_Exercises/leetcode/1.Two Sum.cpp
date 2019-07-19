#include<iostream>
#include<vector>

/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

/*
Runtime: 96 ms, faster than 40.68% of C++ online submissions for Two Sum.
Memory Usage: 9.3 MB, less than 74.10% of C++ online submissions for Two Sum.
*/
std::vector<int> twoSum(std::vector<int>& nums, int target) {
	for (int i = 0; i < nums.size();i++) {
		int remain = target - nums[i];
		auto result = std::find(nums.begin()+i+1, nums.end(), remain);
		if (result != nums.end()) {
			int n = result - nums.begin();
			return std::vector<int> {i, n};
		}
	}
	return std::vector<int>{0,0};
}

int main() {
	std::vector<int> nums{ 3,2,4 };
	int target =6;
	auto result=twoSum(nums, target);
	for (int n : result) {
		std::cout << n << ",";
	}
	system("pause");
}