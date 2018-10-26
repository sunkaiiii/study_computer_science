#pragma once
#include<algorithm>
#include<string>
#include<vector>
#include<list>
#include<memory>

struct Node {
	int i;
	int n;

};


struct TreeNode {
	Node node;
	std::shared_ptr<TreeNode> left;
	std::shared_ptr<TreeNode> right;

	bool operator<(const TreeNode &other) {
		return this->node.n < other.node.n;
	}
};

std::shared_ptr<TreeNode> huffman(std::list<TreeNode> nodes) {
	//对所有的权值进行排序
	nodes.sort();
	std::shared_ptr<TreeNode> root = nullptr;
	while (nodes.size() > 1) {
		//创建新的父节点
		std::shared_ptr<TreeNode> rootNode = std::make_shared<TreeNode>();
		//把当前链表的最前面节点当做新父节点的叶子结点
		rootNode->left = std::make_shared<TreeNode>(nodes.front());;
		nodes.pop_front();
		rootNode->right = std::make_shared<TreeNode>(nodes.front());;
		nodes.pop_front();
		//权值相加
		rootNode->node.n = rootNode->left->node.n + rootNode->right->node.n;
		//更新顶部节点
		root = rootNode;
		//按照权值，将新的节点插入到有序链表中
		auto node = nodes.begin();
		for (;;) {
			if (node == nodes.end()) {
				nodes.insert(node, *rootNode);
				break;
			}
			if (node->node.n>root->node.n) {
				nodes.insert(node, *rootNode);
				break;
			}
			node++;
		}
	}
	return root;
}