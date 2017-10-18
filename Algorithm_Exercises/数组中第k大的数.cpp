#include<iostream>
void Swap(int *a,int *b)
{
  int temp=*a;
  *a=*b;
  *b=temp;
}

int Partition(int data[],int length,int start,int end)
{
  if(data==NULL||length<=0||start<0||end>=length)
    std::cerr << "Invalid Parameters" << '\n';
  int index=start;
  Swap(&data[index],&data[end]);
  int small=start-1;
  for(int index=start;index<end;++index)
  {
    if(data[index]<data[end])
    {
      ++small;
      if(small!=index)
        Swap(&data[index],&data[small]);
    }
  }
  ++small;
  Swap(&data[small],&data[end]);
  return small;
}

int GetLeastNumbers(int* input,int n,int k)
{
  if(input==NULL||k>n||n<=0||k<=0)
  {
    return -1;
  }
  int start=0;
  int end=n-1;
  int index=Partition(input,n,start,end);
  while(index!=k-1)
  {
    if(index>k-1)
    {
      end=index-1;
      index=Partition(input,n,start,end);
    }
    else
    {
      start=index+1;
      index=Partition(input,n,start,end);
    }
  }
  return input[k-1];
}

int main()
{
  int a[]={1,2,3,3,3,3,4,3,6,7};
  std::cout<<GetLeastNumbers(a,sizeof(a)/sizeof(int),4)<<"\n";
}
