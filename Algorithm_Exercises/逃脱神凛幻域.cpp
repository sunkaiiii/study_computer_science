#include<cstdio>
#define N 100002
char s[N];
int a[N],b[N],c[N],d[N];
int main()
{
	int T;
	scanf("%d",&T);
	long long result=0;
	for(int t=0;t<T;t++)
	{
		int n;
		result=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=0;i<n;i++)
		{
			scanf("%d",&b[i]);
		}
		for(int i=0;i<n;i++)
		{
			scanf("%d",&c[i]);
		}
		for(int i=0;i<n;i++)
		{
			scanf("%d",&d[i]);
		}
		for(int i=0;i<n;i++)
		{
			//printf("%d,%d,%d,%d\n",a[i],b[i],c[i],d[i]);
			int index=0;
			int min=a[i];
			if(min>b[i])
			{
				min=b[i];
				index=1;
			}
			if(min>c[i])
			{
				min=c[i];
				index=2;
			}
			if(min>d[i])
			{
				min=d[i];
				index=3;
			}
			switch (index) {
				case 0:
					s[i]='E';
					break;
				case 1:
					s[i]='S';
					break;
				case 2:
					s[i]='W';
					break;
				case 3:
					s[i]='N';
					break;
			}
			result+=min;
		}
		s[n]='\0';
		printf("%ld\n",result);
		for(int i=0;i<n;i++)
		{
			printf("%c",s[i]);
		}
		printf("\n");
	}
}
