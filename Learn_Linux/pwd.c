/*
模拟系统PWD的程序
从当前目录不断上探，知道到/为止，并输出路径
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
ino_t get_inode(char *);
void printpathto(int_t);
void inum_to_name(ino_t,char *,int);

int main()
{
	printpathto(get_inode("."));
	putchar('\n');
	return 0;
}

void printpathto(ino_t this_inode)
{
	/*打印路径，通过不断上探寻找i节点*/
	ino_t my_inode;
	char its_name[BUFSIZ];
	if(get_inode("..")!=this_inode)
	{
		chdir("..");
		inum_to_name(this_inode,its_name,BUFSIZ);
		my_inode=get_inode(".");
		printpathto(my_inode);
		printf("/%s",its_name);
	}
}

void inum_to_name(ino_t inode_to_find,char *namebuf,int buflen)
{
	/*遍历当前目录，寻找和这个i节点同节点号的文件*/
	DIR *dir_ptr;
	struct dirent *direntp;
	dir_ptr=opendir(".");
	if(dir_ptr==NULL)
	{
		perror(".");
		exit(1);
	}
	/*寻找目录下对应的文件*/
	while((direntp=readdir(dir_ptr))!=NULL)
	{
		if(direntp->d_ino==inode_to_find)
		{
			strncpy(namebuf,direntp->d_name,buflen);
			namebuf[buflen-1]='\0'; //以防万一
			closedir(dir_ptr);
			return;
		}
	}
	fprintf(stderr, "error looking for unum %d\n",inode_to_find );
	exit(1);
}

ino_t get_inode(char *fname)
{
	/*返回i节点编号*/
	struct stat info;
	if(stat(fname,&info)==-1)
	{
		fprintf(stderr,"Cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}