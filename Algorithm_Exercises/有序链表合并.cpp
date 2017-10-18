#include<iostream>
struct node
{
    int data;
    struct node* next;
};
void push(struct node** head_ref, int new_data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}
/*
*递归的版本
*/
node* Merge(node* pHead1,node* pHead2)
{
	if(pHead1==NULL)
		return pHead2;
	else if(pHead2==NULL)
		return pHead1;
	node* pMergeHead=NULL;
	if(pHead1->data<pHead2->data)
	{
		pMergeHead=pHead1;
		pMergeHead->next=Merge(pHead1->next,pHead2);
	}
	else
	{
		pMergeHead=pHead2;
		pMergeHead->next=Merge(pHead1,pHead2->next);
	}
	return pMergeHead;
}
/*
*非递归的版本
*/
node* Merge2(node *list1,node *list2)
{
	if(list1==NULL)
		return list2;
	if(list2==NULL)
		return list1;
	node *head=NULL;
	node *p=NULL;
	if(list1->data<=list2->data)
	{
		head=list1;
		list1=list1->next;
	}
	else
	{
		head=list2;
		list2=list2->next;
	}
	p=head;
	while(list1!=NULL&&list2!=NULL)
	{
		if(list1->data<=list2->data)
		{
			p->next=list1;
			list1=list1->next;
			p=p->next;
		}
		else
		{
			p->next=list2;
			list2=list2->next;
			p=p->next;
		}
	}
	if(list1!=NULL)
	{
		p->next=list1;
	}
	else
	{
		p->next=list2;
	}
	return head;
}
void print(node *head)
{
	node* node=head;
	while(node!=NULL)
	{
		std::cout<<node->data<<" ";
		node=node->next;
	}
	std::cout<<"\n";
}
void printAddress(node* head)
{
	node* node=head;
	while(node!=NULL)
	{
		std::cout<<node<<" ";
		node=node->next;
	}
	std::cout<<"\n";
}
int main()
{
	node* a=NULL;
	node* b=NULL;

  push(&a, 15);
  push(&a, 10);
  push(&a, 5);
	printAddress(a);
  push(&b, 20);
  push(&b, 3);
  push(&b, 2);
	printAddress(b);
	node*  merge=NULL;
	merge=Merge2(a,b);
	print(merge);
	printAddress(merge);
}
