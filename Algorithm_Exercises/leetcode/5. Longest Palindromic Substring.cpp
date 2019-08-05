#include <iostream>
#include<string>
using std::string;
//Given a string s, find the longest palindromic substring in s.You may assume that the maximum length of s is 1000.
//Runtime: 752 ms, faster than 5.01% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage : 8.7 MB, less than 95.11 % of C++ online submissions for Longest Palindromic Substring.
string longestPalindrome(string s) {
	int bound = -1;
	string result;
	for (auto i = s.begin(); i != s.end(); i++) {
		if (s.end() - i < bound)
			return result;
		for (auto p = s.end(); p != i; p--) {
			if (s.end() - i < bound)
				return result;
			auto cur = i;
			auto tail = p;
			while (*(--tail) != *i);
			bool ok = true;
			auto j = tail;
			while (true) {
				if (j == cur || j - cur < 0)
					break;
				if (*(++cur) != *(--j)) {
					ok = false;
					break;
				}
			}
			if (ok) {
				if (tail - i > bound) {
					result = s.substr(i - s.begin(), tail - i + 1);
					bound = tail - i;
				}
				break;
			}
		}
	}
	return result;
}

int main() {
	string s;
	std::cin >> s;
	std::cout << longestPalindrome(s)<<std::endl;
}