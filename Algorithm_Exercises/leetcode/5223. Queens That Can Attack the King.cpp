//On an 8x8 chessboard, there can be multiple Black Queensand one White King.
//Given an array of integer coordinates queens that represents the positions of the Black Queens, and a pair of coordinates king that represent the position of the White King, 
//return the coordinates of all the queens(in any order) that can attack the King.
#include <vector>
#include <iostream>
#include <algorithm>
#include<map>
using std::vector;
using std::string;
vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
	int x = king[0];
	int y = king[1];
	vector<vector<int>> result;
	bool ok = true;
	std::map<std::pair<int, int>, bool> temp;
	for (auto i : queens)
	{
		std::pair<int, int> a{ i[0],i[1] };
		temp[a] = true;
	}
	for (int i = x-1; i<8&&ok;)
	{
		std::pair<int, int> a{ i,y };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{i, y});
			if (i < x)
			{
				i = x;
			}
			else {
				ok = false;
			}
		}
		if (i <= 0)
		{
			i = x;
		}
		if (i < x)
		{
			i--;
		}
		else
		{
			i++;
		}
	}
	ok = true;
	for (int i = y-1; i < 8 && ok;)
	{
		std::pair<int, int> a{ x,i };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{ x,i });
			if (i < y)
			{
				i = y;
			}
			else {
				ok = false;
			}
		}
		if (i <= 0)
		{
			i = y;
		}
		if (i < y)
		{
			i--;
		}
		else {
			i++;
		}
	}
	ok = true;
	for (int i = x-1, j = y-1; i >= 0 && j >= 0&&i<8&&j<8&&ok;)
	{
		std::pair<int, int>a{ i,j };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{i, j});
			ok = false;
		}
		i--;
		j--;
	}
	ok = true;
	for (int i = x + 1, j = y + 1; i >= 0 && j >= 0 && i < 8 && j < 8&&ok;)
	{
		std::pair<int, int>a{ i,j };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{i, j});
			ok = false;
		}
		i++;
		j++;
	}
	ok = true;
	for (int i = x + 1, j = y - 1; i >= 0 && j >= 0 && i < 8 && j < 8&&ok;)
	{
		std::pair<int, int>a{ i,j };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{i, j});
			ok = false;
		}
		i++;
		j--;
	}
	ok = true;
	for (int i = x - 1, j = y + 1; i >= 0 && j >= 0 && i < 8 && j < 8&&ok;)
	{
		std::pair<int, int>a{ i,j };
		if (temp.find(a) != temp.end())
		{
			result.push_back(std::vector<int>{i, j});
			ok = false;
		}
		i--;
		j++;
	}
	return result;
}


int main()
{
	vector<vector<int>> a{ {0,1},{1,0},{4,0},{3,3},{2,4} };
	vector<int> b{ 0,0 };
	queensAttacktheKing(a, b);
}