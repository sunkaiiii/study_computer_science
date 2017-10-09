#include<iostream>
struct ListNode
{
	int value;
	ListNode *next;
};

ListNode* FindKthToTail(ListNode* pListHead,int k)
{
	if(pListHead==NULL||k<=0)
		return NULL;
	ListNode *pAhead=pListHead;
	ListNode *pBehind=NULL;
	for(int i=0;i<k;i++)
	{
		if(pAhead->next!=NULL)
			pAhead=pAhead->next;
		else
		{
			return NULL;
		}
	}
	pBehind=pListHead;
	while(pAhead->next!=NULL)
	{
		pAhead=pAhead->next;
		pBehind=pBehind->next;
	}
	ListNode *show=pBehind;
	while(show->next!=NULL)
	{
		std::cout<<show->value<<" ";
		show=show->next;
	}
	std::cout<<std::endl;
	return pBehind;
}
int main()
{
	ListNode *head=new ListNode;
	ListNode *node=head;
	for(int i=0;i<10;i++)
	{
		std::cin>>node->value;
		node->next=new ListNode;
		node=node->next;
		node->next=NULL;
	}
	FindKthToTail(head,5);
}
