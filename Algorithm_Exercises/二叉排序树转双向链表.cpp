#include<iostream>
struct BinaryTreeNode
{
  int value;
  BinaryTreeNode *left=NULL;
  BinaryTreeNode *right=NULL;
};
void convertNode(BinaryTreeNode *pNode,BinaryTreeNode **pLastNode)
{
  if(pNode==NULL)
    return;
  BinaryTreeNode *pCurrent=pNode;
  if(pCurrent->left!=NULL)
    convertNode(pCurrent->left,pLastNode);
  pCurrent->left=*pLastNode;
  if(*pLastNode!=NULL)
    (*pLastNode)->right=pCurrent;
  *pLastNode=pCurrent;
  if(pCurrent->right!=NULL)
    convertNode(pCurrent->right,pLastNode);
}
BinaryTreeNode* convert(BinaryTreeNode* pRoot)
{
  BinaryTreeNode *pLastNode=NULL;
  convertNode(pRoot,&pLastNode);
  //pLast指向双向链表的尾结点
  //现在需要返回头节点
  BinaryTreeNode *pHeadOfList=pLastNode;
  while(pRoot!=NULL&&pHeadOfList->left!=NULL)
  {
    pHeadOfList=pHeadOfList->left;
  }
  return pHeadOfList;
}
int main()
{
  BinaryTreeNode *head;
  head->value=10;
  head->left=new BinaryTreeNode;
  head->left->value=6;
  head->left->left=new BinaryTreeNode;
  head->left->left->value=4;
  head->left->right=new BinaryTreeNode;
  head->left->right->value=8;
  head->right=new BinaryTreeNode;
  head->right->value=14;
  head->right->left=new BinaryTreeNode;
  head->right->left->value=12;
  head->right->right=new BinaryTreeNode;
  head->right->right->value=16;
  BinaryTreeNode *node=convert(head);
  while (node!=NULL) {
    std::cout<<node->value<<" ";
    node=node->right;
  }
  std::cout<<"\n";
}
