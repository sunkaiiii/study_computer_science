/*ls.c
模拟linux中ls命令
可以有参数目录名，如果没有参数则默认为当前目录
*/
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char[]);

int main(int ac,char *av[])
{
	if(ac==1)
	{
		do_ls(".");
	}
	else
	{
		while(--ac)
		{
			printf("\%s:\n",*++av);
			do_ls(*av);
		}
	}
	return 0;
}
void do_ls(char dirname[])
{
	DIR *dir_ptr; //目录
	// struct dirent *direntp; //每一个文件
	struct dirent **dirlist;

	if((dir_ptr=opendir(dirname))==NULL)
		fprintf(stderr, "ls1:cannot open %s\n",dirname );
	else
	{
		int size=scandir(dirname,&dirlist,0,alphasort); //此处修改实现输出的结果按照文件名进行排序
		for(int i=0;i<size;i++)
		{
			printf("\%s\n",dirlist[i]->d_name);
		}
		// while((direntp=readdir(dir_ptr))!=NULL)
		// {
		// 	pritnf("%s\n",direntp->d_name);
		// }
		closedir(dir_ptr);
	}
}