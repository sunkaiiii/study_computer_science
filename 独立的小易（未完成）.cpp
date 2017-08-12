#include<iostream>
int main()
{
	int x,f,d,p;
	std::cin>>x>>f>>d>>p;
	int result=0;
	int fangzi=d/x;
	int tao=d/p;
	for(int i=0;i<tao;i++)
	{
		for(int i2=0;i2<fangzi;i2++)
		{
			if((d-(p*i)-(x*i2))<0)
				break;
			if(i+f<=i2)
			{
				if(i+f>result)
					result=i+f;
			}
			else
			{
				if(i2>result)
				{
					result=i2;
				}
			}
		}
	}
	std::cout<<result;
}
