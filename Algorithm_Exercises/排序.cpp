#include<iostream>
#include<vector>
void qsort(int a[],int low,int high)
{
	if(low>high)
		return;
	int key=a[low];
	int front=low;
	int last=high;
	while(front<last)
	{
		while(front<last&&a[last]>=key)
		{
			last--;
		}
		a[front]=a[last];
		while(front<last&&a[front]<=key)
		{
			front++;
		}
		a[last]=a[front];
	}
	a[front]=key;
	qsort(a,low,front-1);
	qsort(a,front+1,high);
}
void Merge(int a[],int start,int mid,int end,int temp[])
{
	int i=start,j=mid+1,k=start;
	// std::cout<<start<<" "<<mid<<" "<<end<<std::endl;
	while(i!=mid+1&&j!=end+1)
	{
		if(a[i]>a[j])
		{
			temp[k++]=a[j++];
		}
		else
		{
			temp[k++]=a[i++];
		}
	}
	while(i!=mid+1)
		temp[k++]=a[i++];
	while(j!=end+1)
		temp[k++]=a[j++];
	for(i=start;i<=end;i++)
	{
		a[i]=temp[i];
	}
}
void MergeSort(int a[],int start,int end,int temp[])
{
	int mid;
	if(start<end)
	{
		mid=(start+end)/2;
		MergeSort(a,start,mid,temp);
		MergeSort(a,mid+1,end,temp);
		Merge(a,start,mid,end,temp);
	}
}

int main()
{
	int a[]={67,5,4,44,3,76,12,8,1,3};
	int b[sizeof(a)/sizeof(int)]={0};
	qsort(a,0,sizeof(a)/sizeof(int)-1);
	// MergeSort(a,0,sizeof(a)/sizeof(int)-1,b);
	for(int i=0;i<sizeof(a)/sizeof(int);i++)
		std::cout<<a[i]<<" ";
}
