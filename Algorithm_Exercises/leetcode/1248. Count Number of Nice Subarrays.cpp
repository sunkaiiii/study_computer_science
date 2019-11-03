#include <vector>
#include <iostream>
#include <algorithm>
#include<deque>
#include<unordered_map>
using std::vector;
using std::string;
//Runtime: 196 ms, faster than 25.00 % of C++ online submissions for Count Number of Nice Subarrays.
//Memory Usage : 18.5 MB, less than 100.00 % of C++ online submissions for Count Number of Nice Subarrays.
//Given an array of integers numsand an integer k.A subarray is called nice if there are k odd numbers on it.
//Return the number of nice sub - arrays.
//Example 1:
//Input: nums = [1, 1, 2, 1, 1], k = 3
//Output : 2
//Explanation : The only sub - arrays with 3 odd numbers are[1, 1, 2, 1] and [1, 2, 1, 1].
//Example 2 :
//	Input : nums = [2, 4, 6], k = 1
//	Output : 0
//	Explanation : There is no odd numbers in the array.
//	Example 3 :
//	Input : nums = [2, 2, 2, 1, 2, 2, 1, 2, 2, 2], k = 2
//	Output : 16
int numberOfSubarrays(vector<int>& nums, int k) {
	int odd = 0;
	int result = 0;
	std::deque<int> temp;
	for (int i = 0; i < k; i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < nums.size(); i++)
	{
		if ((nums[i] % 2) != 0)
		{
			temp[odd++] = i;
			if (odd == k)
			{
				int a = temp[0];
				int b = temp[k - 1];
				int countLeft = 1;
				int countRight = 1;
				while (a > 0 && nums[a - 1] % 2 == 0)
				{
					a--;
					countLeft++;
				}
				while (b < nums.size() - 1 && nums[b + 1] % 2 == 0)
				{
					b++;
					countRight++;
				}
				result = result + countLeft * countRight;
				temp.pop_front();
				temp.push_back(0);
				odd--;
			}
		}
	}
	return result;
}

int main()
{
	std::vector<int> v{ 33638,68647,19451,77078,82905,28725,39979,72613,56309,52947,35686,13228,11103,45827,73787,22573,92402,94287,89489,19802,94212,28119,99817,59878,96293,17294,9521,86077,49711,71143 };
	std::cout << numberOfSubarrays(v,10);
}