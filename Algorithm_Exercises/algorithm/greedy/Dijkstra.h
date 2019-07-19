#pragma once
#include <map>
#include <vector>
std::map<int, std::map<int, int>> getExample();
std::vector<int> findRoad(int startPoint, std::map<int, std::map<int, int>> example);