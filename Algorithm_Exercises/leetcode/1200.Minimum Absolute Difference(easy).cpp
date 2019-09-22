//Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements. 

//Return a list of pairs in ascending order(with respect to pairs), each pair[a, b] follows
//Input: arr = [4, 2, 1, 3]
//Output : [[1, 2], [2, 3], [3, 4]]
//Explanation : The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;
vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
	std::sort(arr.begin(), arr.end());
	vector<vector<int>> result;
	int diff = 0;
	for (int i = 1; i < arr.size(); i++)
	{
		if (diff == 0)
		{
			result.push_back(vector<int>{arr[i - 1], arr[i]});
			diff = arr[i] - arr[i-1];
			continue;
		}
		if(arr[i] - arr[i - 1] < diff)
		{
			diff = diff = arr[i] - arr[i - 1];;
			result.clear();
			result.push_back(vector<int>{arr[i - 1], arr[i]});
		}
		else if (arr[i] - arr[i - 1] == diff)
		{
			result.push_back(vector<int>{arr[i - 1], arr[i]});
		}
	}
	return result;
}

void f(vector<vector<int>>& arr)
{
	for (auto i : arr)
	{
		std::cout << "[";
		for (auto j : i)
		{
			std::cout <<j << ",";
		}
		std::cout << "]";
	}
	std::cout << std::endl;
}

int main()
{
	vector<int> arr = { 4,2,1,3 };
	auto arr2=minimumAbsDifference(arr);
	f(arr2);
	arr = { 1,3,6,10,15 };
	arr2=minimumAbsDifference(arr);
	f(arr2);
	arr = { 3,8,-10,23,19,-4,-14,27 };
	arr2 = minimumAbsDifference(arr);
	f(arr2);
}