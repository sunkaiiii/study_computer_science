#include"greedySelect.h"
#include"schedule.h"
#include"huffman.h"
#include<iostream>

void frontErgodicTree(std::shared_ptr<TreeNode> root) {
	std::cout << root->node.n << " ";
	if (root->left != nullptr) {
		frontErgodicTree(root->left);
	}
	if (root->right != nullptr) {
		frontErgodicTree(root->right);
	}
}

void middleErgodicTree(std::shared_ptr<TreeNode> root) {
	if (root->left != nullptr) {
		middleErgodicTree(root->left);
	}
	std::cout << root->node.n << " ";
	if (root->right != nullptr) {
		middleErgodicTree(root->right);
	}
}


int main() {
	//int n;
	//std::cin >> n;
	//std::vector<Activity> activities;
	//while (n--) {
	//	struct Activity activity;
	//	std::cin >> activity.startTime >> activity.endTime;
	//	activities.push_back(activity);
	//}
	//auto result = select(activities);
	//for (Activity activity : result) {
	//	std::cout << activity.startTime << "," << activity.endTime << std::endl;
	//}

	//服务问题
	//int n;
	//std::cin >> n;
	//std::vector<Customer> customers;
	//while (n--) {
	//	struct Customer customer;
	//	std::cin >> customer.serveTime >> customer.hopeTime;
	//	customers.push_back(customer);
	//}
	//std::cout << schedule(customers) << std::endl;

	int n;
	std::cin >> n;
	std::list<TreeNode> nodes;
	while (n--) {
		struct TreeNode node;
		std::cin >> node.node.n;
		nodes.push_back(node);
	}
	auto root = huffman(nodes);

	//frontErgodicTree(root);
	//std::cout << std::endl;
	//middleErgodicTree(root);
	//std::cout << std::endl;
	system("pause");
}
