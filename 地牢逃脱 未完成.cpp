#include<iostream>
#include<cmath>
#include<string.h>
int result=0;
int minstep=9999999;
char a[52][52];
int x,y;
void f(int smovex[],int smovey[],int posx,int posy,int finaly,int finalx,int step,int k,int lastposx,int lastposy)
{
	std::cout<<posy<<','<<posx<<std::endl; 
	for(int i=0;i<y;i++)
	{
		for(int i2=0;i2<x;i2++)
		{
			std::cout<<a[i][i2];
		}
		std::cout<<std::endl;
	}
	if(posx==finalx&&posy==finaly)
	{
		if(step<minstep)
			minstep=step;
		return;
	}
	if(fabs(finaly-posy)+fabs(finalx-posx)+step>=minstep)
	{
		return;
	}
	for(int i=0;i<k;i++)
	{
		if(a[posx+smovex[i]][posy+smovey[i]]=='.')
		{
			a[posx+smovex[i]][posy+smovey[i]]='x';
			f(smovex,smovey,posx+smovex[i],posy+smovey[i],finalx,finaly,step+1,k,posx,posy);
			a[posx+smovex[i]][posy+smovey[i]]='.';
			
		}
	}
}
int main()
{
	std::cin>>y>>x;
	int c[52][52];
	for(int i=0;i<y;i++)
	{
		for(int i2=0;i2<x;i2++)
		{
			std::cin>>a[i][i2];
			c[i][i2]=a[i][i2];
		}
	}
	int sx,sy;
	std::cin>>sx>>sy;
	int s;
	std::cin>>s;
	int smovex[s],smovey[s];
	for(int i=0;i<s;i++)
	{
		std::cin>>smovex[i]>>smovey[i];
	}
	for(int iy=0;iy<y;iy++)
	{	
		for(int ix=0;ix<x;ix++)
		{
			if(a[iy][ix]=='.')
			{
				/*std::cout<<a[iy][ix]<<std::endl;
				for(int i=0;i<y;i++)
				{
					for(int i2=0;i2<x;i2++)
					{
						a[i][i2]=c[i][i2];
						std::cout<<a[i][i2];
					}
					std::cout<<std::endl;
				}
				std::cout<<sy<<','<<sx<<','<<iy<<','<<ix<<std::endl;
				*/
				minstep=9999999;
				f(smovex,smovey,sx,sy,ix,iy,0,s,-1,-1);
				//std::cout<<minstep<<std::endl;
				if(minstep>result&&minstep!=9999999)
				{
					result=minstep;
				}
				else if(minstep==9999999)
				{
					std::cout<<-1<<std::endl;
					return 0;
				}
				
			}
		}
	}
	std::cout<<result<<std::endl;
}
