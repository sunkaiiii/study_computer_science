// algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using std::string;

//给定两个字符串a,b。输出最长回文字符串
//其中回文字符串由两个字符串的子串构成，且均为非空，若不存在，则输出-1，字符集为小写字母
//a=abc,b=abc 输出s=aba
//a=acc,b=a 输出s=acca
void findPalindrome(string& s, int i, int j, int& len, int& left)
{
	while (i >= 0 && j < s.size() && s[i] == s[j])
	{
		i--;
		j++;
	}
	i++;
	j--;
	if (j - i + 1 > len)
	{
		len = j - i + 1;
		left = i;
	}
}

string longestPalindrome(string s) {
	int n = s.length();
	if (n < 2)
		return s;
	int left = 0, len = 0;
	for (int i = 0; i < n; i++)
	{
		findPalindrome(s, i, i, len, left);
		if (i + 1 != n && s[i] == s[i + 1]) {
			findPalindrome(s, i, i + 1, len, left);
		}
	}
	return s.substr(left, len);
}

void findLongestPalidrome(string s1, string s2)
{
	int curLenght;
	int s1AnsLst, s1AnsRight, s2AnsLeft, s2AnsRight;
	string result;

	for (int i = 0; i < s1.length(); i++)
	{
		for (int j = i + 1; j <= s1.length(); j++)
		{
			for (int i1 = 0; i1 < s2.length(); i1++)
			{
				for (int j1 = i1 + 1; j1 <= s2.length(); j1++)
				{
					if ((s1.length() - i + s2.length() - j) < result.length())
						break;
					string testString = s1.substr(i, j) + s2.substr(i1, j1);
					//std::cout<<testString<<",";
					string tempresult = longestPalindrome(testString);
					if (tempresult.length() > result.length())
					{
						result = tempresult;
					}
				}
			}

		}
	}
	std::cout << result << std::endl;
}


int main()
{
	string s1, s2;
	std::cin >> s1 >> s2;
	findLongestPalidrome(s1, s2);
}
