#include <iostream>
#include <unordered_map>
#include<string>
using std::string;
//Runtime: 212 ms, faster than 18.73 % of C++ online submissions for Longest Palindromic Substring.
//Memory Usage : 17.5 MB, less than 36.24 % of C++ online submissions for Longest Palindromic Substring.
string longestPalindrome(string s) {
	string result = s.substr(0,1);
	std::unordered_map<char, std::vector<int>> temp;
	for (int i = 0; i < s.length(); i++)
	{
		if (temp.find(s[i]) != temp.end()) {
			for (int tempsi : temp[s[i]]) {
				int left = tempsi;
				int right = i;
				if (right - left + 1 < result.length())
					break;
				bool ok = true;
				while (left < right && ok)
				{
					if (s[++left] != s[--right])
					{
						ok = false;
					}
				}
				if (ok && result.length() < i - tempsi+ 1)
				{
					result = s.substr(tempsi, i - tempsi + 1);
					break;
				}
			}
		}
		temp[s[i]].push_back(i);
	}
	return result;
}

int main() {
	string s;
	std::cin >> s;
	std::cout << longestPalindrome(s)<<std::endl;
}