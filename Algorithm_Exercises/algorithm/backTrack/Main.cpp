#include "Nqueens.h"
#include "MaximumClique.h"
int main() {
	//Nqueen();

	std::map<int, std::vector<int>> graph= {
	{1,{2,3,4,5}},
	{2,{1,4}},
	{3,{1,4,5}},
	{4,{1,2,3,5}},
	{5,{1,3,4}}
	};
	auto result = findMaximumClique(graph);
	for (int i : result) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}