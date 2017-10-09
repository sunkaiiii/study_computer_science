#include<iostream>
struct ListNode
{
	int value;
	ListNode *next;
};

ListNode* ReverseList(ListNode *pHead)
{
	if(pHead==NULL||pHead->next==NULL)
		return pHead;
	ListNode *pre,*cur,*next;
	cur=pHead->next;
	pre=NULL;
	while(cur->next!=NULL)
	{
		next=cur->next;
		cur->next=pre;
		pre=cur;
		cur=next;
	}
	pHead->next=pre;
	return pHead;
}
int main()
{
	ListNode *head=new ListNode;
	ListNode *node=head;
	head->next=new ListNode;
	node=node->next;
	for(int i=0;i<10;i++)
	{
		std::cin>>node->value;
		node->next=new ListNode;
		node=node->next;
		node->next=NULL;
	}
	ReverseList(head);
	node=head->next;
	while(node!=NULL)
	{
		std::cout<<node->value<<" ";
		node=node->next;
	}
	std::cout<<std::endl;
}
