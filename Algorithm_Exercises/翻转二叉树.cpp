#include<iostream>
struct BinaryTreeNode
{
	BinaryTreeNode():value(0),left(NULL),right(NULL){}
	BinaryTreeNode(int i):value(i),left(NULL),right(NULL){}
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};
void MirrorRecursively(BinaryTreeNode *pNode)
{
	if(pNode==NULL||(pNode->left==NULL&&pNode->right==NULL))
	{
		return;
	}
	BinaryTreeNode *temp=pNode->left;
	pNode->left=pNode->right;
	pNode->right=temp;
	if(pNode->left!=NULL)
	{
		MirrorRecursively(pNode->left);
	}
	if(pNode->right!=NULL)
	{
		MirrorRecursively(pNode->right);
	}
}

void print(BinaryTreeNode* pNode)
{
	if(pNode==NULL)
		return;
	std::cout<<pNode->value<<" "; //前序
	print(pNode->left);
	// std::cout<<pNode->value<<" "; //中序
	print(pNode->right);
	// std::cout<<pNode->value<<" "; //后序
}

int main()
{
	BinaryTreeNode *head=new BinaryTreeNode(1);
	head->left=new BinaryTreeNode(2);
	head->right=new BinaryTreeNode(3);
	head->left->left=new BinaryTreeNode(4);
	head->left->right=new BinaryTreeNode(5);
	head->right->left=new BinaryTreeNode(6);
	head->right->right=new BinaryTreeNode(7);
	print(head);
	std::cout<<"\n";
	MirrorRecursively(head);
	print(head);
}
