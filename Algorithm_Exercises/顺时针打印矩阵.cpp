#include<iostream>
void printNumber(int number)
{
	std::cout<<number<<" ";
	return;
}
void PrintMatrixClocksiely(int numbers[4][4],int columns,int rows,int start)
{
	int endX=columns-1-start;
	int endY=rows-1-start;

	for(int i=start;i<=endX;++i)
	{
		int number=numbers[start][i];
		printNumber(number);
	}
	if(start<endY)
	{
		for(int i=start+1;i<=endY;++i)
		{
			int number=numbers[i][endX];
			printNumber(number);
		}
	}
	if(start<endX&&start<endY)
	{
		for(int i=endX-1;i>=start;--i)
		{
			int number=numbers[endY][i];
			printNumber(number);
		}
	}
	if(start<endX&&start<endY-1)
	{
		for(int i=endY-1;i>=start+1;--i)
		{
			int number=numbers[i][start];
			printNumber(number);
		}
	}
}
void PrintMatrixClocksiely(int numbers[4][4],int columns,int rows)
{
	if(numbers==NULL||columns<=0||rows<=0)
		return;
	int start=0;
	//对于打印来说，第一圈左上坐标是(1,1),第二圈是(2,2)
	//可以注意到循环条件是columns>startX*2，并且rows>startY*2
	while(columns>start*2&&rows>start*2)
	{
		PrintMatrixClocksiely(numbers,columns,rows,start);
		++start;
	}
}
int main()
{
	int a[4][4];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			std::cin>>a[i][j];
	PrintMatrixClocksiely(a,4,4);
}
