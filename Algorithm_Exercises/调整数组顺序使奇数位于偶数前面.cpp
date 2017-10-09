#include<iostream>
void ReorderOddEven(int *pData,int length)
{
	if(pData==NULL||length<=0)
		return;
	int *pBegin=pData;
	int *pEnd=pData+length-1;

	while(pBegin<pEnd)
	{
		//向后移动pBegin，直到它指向偶数
		while(pBegin<pEnd&&(*pBegin%2)!=0)
			pBegin++;
		//向前移动pEnd，直到他遇到奇数
		while(pBegin<pEnd&&(*pEnd%2)==0)
			pEnd--;
		if(pBegin<pEnd)
		{
			int t=*pBegin;
			*pBegin=*pEnd;
			*pEnd=t;
		}
	}
}
int main()
{
	int a[10];
	for(int i=0;i<sizeof(a)/sizeof(int);i++)
	{
		std::cin>>a[i];
	}
	ReorderOddEven(a,sizeof(a)/sizeof(int));
	for(int i=0;i<sizeof(a)/sizeof(int);i++)
	{
		std::cout<<a[i]<<" ";
	}
	std::cout<<std::endl;
}
