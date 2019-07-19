#include<iostream>
#include<vector>
#include <unordered_map>

/*
 Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 
 You may assume that each input would have exactly one solution, and you may not use the same element twice.
 
 Example:
 
 Given nums = [2, 7, 11, 15], target = 9,
 
 Because nums[0] + nums[1] = 2 + 7 = 9,
 return [0, 1].
 
 */

/*
 Runtime: 12 ms, faster than 69.59% of C++ online submissions for Two Sum.
 Memory Usage: 11.6 MB, less than 5.05% of C++ online submissions for Two Sum.
 */
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, std::vector<int>> searchTable;
    for(int i=0;i<nums.size();i++){
        searchTable[nums[i]].push_back(i); //构建一个哈希查找表
    }
    for (int i = 0; i < nums.size();i++) {
        int currentNum=nums[i];
        int remain = target - currentNum;
        if(searchTable.find(remain)!=searchTable.end()){ //判断那个相减得到的数字数否在哈希表中
            for(int num:searchTable[remain]){
                if(num!=i){
                    return std::vector<int>{i,num};
                }
            }
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
}
