#include<iostream>
struct ListNode
{
	int value;
	ListNode *next;
};

ListNode* Merge(ListNode* pHead1,ListNode* pHead2)
{
	if(pHead1->next==NULL)
		return pHead2;
	else if(pHead2->next==NULL)
		return pHead1;
	ListNode *pMerge=NULL;
	if(pHead1->value<pHead2->value)
	{
		pMerge=pHead1;
		pMerge->next=Merge(pHead1->next,pHead2);
	}
	else
	{
		pMerge=pHead2;
		pMerge->next=Merge(pHead1,pHead2->next);
	}
	return pMerge;
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
	ListNode *head2=new ListNode;
	ListNode *node2=head2;
	for(int i=0;i<8;i++)
	{
		std::cin>>node2->value;
		node2->next=new ListNode;
		node2=node2->next;
		node2->next=NULL;
	}
	ListNode *mergeHead=Merge(head,head2);
	while(mergeHead->next!=NULL)
	{
		std::cout<<mergeHead->value<<" ";
		mergeHead=mergeHead->next;
	}
	std::cout<<std::endl;
}
