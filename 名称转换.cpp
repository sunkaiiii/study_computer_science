#include<iostream>
#include<cstring>
bool isDaxie(char a)
{
	if(a>='A'&&a<='Z')
		return true;
	return false;
}
bool isXiaoxie(char a)
{
	if(a>='a'&&a<='z')
		return true;
	return false;
}
bool isShuzi(char a)
{
	if(a>='0'&&a<='9')
		return true;
	return false;
}
int main()
{
	char a[1000000];
	while(std::cin>>a)
	{
		int indexa=0;
		int indexb=0;
		char b[1000008];
		int daxie=0;
		int danci=0;
		for(;indexa<strlen(a);indexa++)
		{
			if(a[indexa]=='.')
			{
				b[indexb++]='_';
			}
			else if(danci==0)
			{
				if(isShuzi(a[indexa]))
				{
					danci=1;
					if(a[indexa-1]!='.')
						b[indexb++]='_';
					b[indexb++]=a[indexa];
				}
				else if(isDaxie(a[indexa]))
				{
					danci=1;
					if(a[indexa-1]!='.')
						b[indexb++]='_';
					b[indexb++]=a[indexa];
				}
				else if(isXiaoxie(a[indexa]))
				{
					danci=1;
					if(a[indexa-1]!='.')
						b[indexb++]='_';
					b[indexb++]=a[indexa]-32;
				}
			}
			else if(danci==1)
			{
				if(isDaxie(a[indexa])&&isXiaoxie(a[indexa+1]))
				{
					if(a[indexa-1]!='.')
						b[indexb++]='_';
					b[indexb++]=a[indexa];
				}
				else if(isShuzi(a[indexa])&&!isShuzi(a[indexa-1]))
				{
					if(a[indexa-1]!='.')
						b[indexb++]='_';
					b[indexb++]=a[indexa];
				}
				else if(isShuzi(a[indexa]))
				{
					b[indexb++]=a[indexa];
				}
				else if(isXiaoxie(a[indexa]))
				{
					b[indexb++]=a[indexa]-32;
				}
				else if(isDaxie(a[indexa]))
				{
					b[indexb++]=a[indexa];
				}
			}
		}
		b[indexb++]='_';
		b[indexb]=0;
		std::cout<<b<<std::endl;
	}
}
