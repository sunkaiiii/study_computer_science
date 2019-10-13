//Balanced strings are those who have equal quantity of 'L' and 'R' characters.
//Given a balanced string s split it in the maximum amount of balanced strings.
//Return the maximum amount of splitted balanced strings.
//Input: s = "RLRRLLRLRL"
//Output : 4
//Explanation : s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
//
//Input : s = "RLLLLRRRLR"
//Output : 3
//Explanation : s can be split into "RL", "LLLRRR", "LR", each substring contains same number of 'L' and 'R'.
#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;
using std::string;
int balancedStringSplit(string s) {
	int l = 0;
	int r = 0;
	int result = 0;
	for (char c : s)
	{
		if (c == 'L')
		{
			l++;
		}
		else if (c == 'R')
		{
			r++;
		}
		if (l != 0 && l == r)
		{
			result++;
			l = 0;
			r = 0;
		}
	}
	return result;
}


int main()
{
	std::cout << balancedStringSplit("RLRRLLRLRL");
	std::cout << balancedStringSplit("RLLLLRRRLR");
	std::cout << balancedStringSplit("LLLLRRRR");
}