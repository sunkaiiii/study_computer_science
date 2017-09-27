#include<iostream>
#include<cmath>
int a[100001];
int main()
{
	int a,b;
	std::cin>>a>>b;
	if(a%b==0)
	{
		std::cout<<a/b;
	}
	else
	{
		int i=0;
		int count=0;
		double result=double(a)/double(b);
		int index=0,temp,weizhi;
		int ok=0;
		int ishasnum=0;
		while(i<8&&!ok)
		{
			temp=int((result*10))%10;
			result*=10;
			//std::cout<<weizhi<<","<<temp<<std::endl;
			if(temp!=0)
			{
				ishasnum=1;
				if(index==temp)
				{
					count++;
				}
				else
				{
					index=temp;
					weizhi=i;
					count=0;
				}
				if(count>3)
				{

					ok=1;
					break;
				}
			}
			else
			{
				if(ishasnum)
				{
					count++;
				}
				if(count>3)
				{
					ok=0;
					break;
				}
			}
			i++;
		}
		//std::cout<<ok;
		if(ok)
		{
			double result=double(a)/double(b);
			std::cout<<int(result)<<".";
			result=result-int(result);
			while(weizhi>0)
			{
				result=result*10;
				std::cout<<int(result)%10;
				weizhi--;
			}
			std::cout<<"("<<index<<")"<<std::endl;
		}
		else
		{
			float result=double(a)/double(b);
			std::cout<<result<<std::endl;
		}
	}
}
