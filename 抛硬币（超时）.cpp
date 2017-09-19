#include<iostream>
short a[2][10000001];
int main()
{
	int b;
	while(std::cin>>b)
	{
		int d, e;
		a[0][0] = 1;
		a[1][0] = 1;
		a[1][1] = 1;
		for (d = 0; d <= b; d++)
		{
			for (e = 0; e <= d; e++)
			{
				if (e == 0)
					a[d%2][e] = 1;
				else
					a[d%2][e] = (a[(d - 1)%2][e] + a[(d - 1)%2][e - 1])%2;
			}
		}
			int odd=0;
			for (e = 0; e <= b; e++)
			{
				if(a[b%2][e]%2!=0)
					odd++;
			}
			std::cout<<odd<<std::endl<<(b+1)-odd<<std::endl;
		}
		return 0;
}
