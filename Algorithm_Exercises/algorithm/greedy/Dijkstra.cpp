#include "Dijkstra.h"

std::map<int, std::map<int, int>> getExample()
{
	//生成一个有向图用例
	return std::map<int, std::map<int, int>> {
		{1, {{2,10},{6,3}}},
		{ 2,{{3,7} } },
		{3,{}},
		{4,{{1,3},{3,4},{5,7} }},
		{5,{}},
		{ 6,{{2,2},{5,1}, {4,6}} }
	};
	
	
}

std::vector<int> findRoad(int startPoint,std::map<int, std::map<int, int>> example)
{
	if (startPoint >= example.size()) { //错误处理
		return std::vector<int>{};
	}
	//***********************
	//数据初始化
	std::vector<int> s;
	int n = example.size();
	const int infinity = 0x0fffffff;
	std::vector<int> l(n+1);
	std::vector<int> distances(n+1,infinity);
	distances[startPoint] = 0;
	auto startPosition = example[startPoint];
	s.push_back(startPoint);
	int currentPoint = startPoint;
	//***************************
	//开始循环
	while (s.size() <n) {
		for (auto eachPoint : example[currentPoint]) { 
			//开始取点，并更新维护的距离表
			//如果从当前点走到他所连接的点的距离要小于记录里面的距离
			//则更新记录里的距离为从当前点的记录距离（肯定是最小的）加上权值
			//同时更新数组l，将目标点的最短路径来源更新闻当前点。
			if (distances[currentPoint] + eachPoint.second < distances[eachPoint.first]) {
				distances[eachPoint.first] = distances[currentPoint] + eachPoint.second;
				l[eachPoint.first] = currentPoint;
			}
		}
		example.erase(currentPoint);
		int min = infinity;
		int j = -1;
		//更新过一次之后，从剩余的点里面找到记录的距离最短的那个
		//取出并开始下一次循环
		for (auto remainedPoint : example) {
			if (distances[remainedPoint.first] < min) {
				j = remainedPoint.first;
				min = distances[remainedPoint.first];
			}
		}
		s.push_back(j);
		currentPoint = j;
	}
	distances.erase(distances.begin());
	return distances;
}
