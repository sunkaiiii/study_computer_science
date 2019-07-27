#include<iostream>
#include<string>
#include<algorithm>
using std::string;
/*
Given a string, find the length of the longest substring without repeating characters.
Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Runtime: 12 ms, faster than 84.79% of C++ online submissions for Longest Substring Without Repeating Characters.
Memory Usage: 9 MB, less than 96.98% of C++ online submissions for Longest Substring Without Repeating Characters.
*/
int lengthOfLongestSubstring(string s) {
	int resultNum = 0;
	auto currentIndex = s.begin();
	for (auto c = s.begin(); c != s.end();c++) {
		if (std::find(currentIndex,c,*c)!=c) {
			resultNum = c - currentIndex > resultNum ? c - currentIndex : resultNum;
			while (*(currentIndex++) != *c);
		}
	}
	return s.end()-currentIndex>resultNum?s.end()-currentIndex:resultNum;
}
int main() {
	string s;
	std::cin >> s;
	std::cout << lengthOfLongestSubstring(s);
}