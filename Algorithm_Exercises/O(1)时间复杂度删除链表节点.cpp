#include<iostream>
struct list
{
	list *next=NULL;
	int value;
};

void DeleteNode(list **head,list *toBeDelete)
{
	if(!head||!toBeDelete)
		return;

	//要删除的节点不是尾结点
	if(toBeDelete->next!=NULL)
	{
		list *pNext=toBeDelete->next;
		toBeDelete->value=pNext->value;
		toBeDelete->next=pNext->next;

		delete pNext;
		pNext=NULL;
	}
	//链表只有一个结点，删除头结点
	else if(*head==toBeDelete)
	{
		delete toBeDelete;
		toBeDelete=NULL;
		head=NULL;
	}
	//链表中有多个节点，且删除的是尾结点
	else
	{
		list *pNode=*head;
		while(pNode->next!=toBeDelete)
			pNode=pNode->next;
		pNode->next=NULL;
		delete toBeDelete;
		toBeDelete=NULL;
	}
}
int main()
{
	list *a=new list;
	list *node=a;;
	for(int i=0;i<10;i++)
	{
		std::cin>>node->value;
		node->next=new list;
		node=node->next;
	}
	node=a;
	while (node->next!=NULL)
	{
		node=node->next;
	}
	DeleteNode(&a,node);
	node=a;
	while (node->next!=NULL) {
		std::cout<<node->value<<" ";
		node=node->next;
	}
	std::cout<<std::endl;

}
