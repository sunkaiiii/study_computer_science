#include "MaximumClique.h"
auto isOutboundFunction = [](int  level,int size, int current, int bound) { return size-level + current > bound; }; //界限函数

void mainAlgorithm(std::map<int, std::vector<int>>& graph, std::vector<int>& temp, std::map<int, std::vector<int>>::iterator it,int level, int current, int& bound,std::vector<int> &result)
{
	if (it == graph.end()) {
		return;
	}
	if (!isOutboundFunction(level,graph.size(), current, bound)) //判断剩余的节点数量是否能够超过界
		return;
	bool ok = true;
	for (int i = 1; i != it->first && ok; i++) { //判断当前节点是否在团当中
		if (temp[i] == 1) {
			auto points = graph[i];
			ok = std::find(points.begin(), points.end(), it->first) != points.end();
		}
	}
	if (ok) { //如果判断通过，则将节点入团
		temp[it->first] = 1;
		current++;
		if (current > bound) {
			result = temp;
			bound = current;
		}
		mainAlgorithm(graph, temp, ++it, level+1, current--, bound,result);
		temp[(--it)->first] = 0; //走右分支，不入团，在这里恢复一下状态。
	}
	mainAlgorithm(graph, temp, ++it, level+1, current, bound,result);
	--it;
}

std::vector<int> findMaximumClique(std::map<int, std::vector<int>>& graph) {
	int bound = 0;
	int current = 0;
	int level = 0;
	std::vector<int> temp(graph.size() + 1);
	std::vector<int> result(graph.size()+1);
	mainAlgorithm(graph, temp,graph.begin(),level, current,bound,result);
	return result;
}

