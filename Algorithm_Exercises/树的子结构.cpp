#include<iostream>
struct BinaryTreeNode
{
	int value;
	BinaryTreeNode *left=NULL;
	BinaryTreeNode *right=NULL;
};

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2)
{
	if(pRoot2==NULL)
		return true;
	if(pRoot1==NULL)
		return false;
	if(pRoot1->value!=pRoot2->value)
		return false;
	return DoesTree1HaveTree2(pRoot1->left,pRoot2->left)&&DoesTree1HaveTree2(pRoot1->right,pRoot2->right);
}

bool HasSubTree(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2)
{
	bool result=false;

	if(pRoot1!=NULL&&pRoot2!=NULL)
	{
		if(pRoot1->value==pRoot2->value)
		{
			result=DoesTree1HaveTree2(pRoot1,pRoot2);
		}
		if(!result)
			result=HasSubTree(pRoot1->left,pRoot2);
		if(!result)
			result=HasSubTree(pRoot1->right,pRoot2);
	}
	return result;
}

int main()
{
	BinaryTreeNode *head,*head2;
	head=new BinaryTreeNode;
	head2=new BinaryTreeNode;
	head->value=8;
	head->left=new BinaryTreeNode;
	head->left->value=8;
	head->left->left=new BinaryTreeNode;
	head->left->left->value=9;
	head->left->right=new BinaryTreeNode;
	head->left->right->value=2;
	head->left->right->left=new BinaryTreeNode;
	head->left->right->left->value=4;
	head->left->right->right=new BinaryTreeNode;
	head->left->right->right->value=7;
	head->right=new BinaryTreeNode;
	head->right->value=7;
	head2->value=8;
	head2->left=new BinaryTreeNode;
	head2->left->value=9;
	head2->right=new BinaryTreeNode;
	head2->right->value=2;
	std::cout<<HasSubTree(head,head2)<<std::endl;
}
