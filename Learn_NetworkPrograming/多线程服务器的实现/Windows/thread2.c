#include<stdio.h>
#include<Windows.h>
#include<process.h>

unsigned WINAPI ThreadFunc(void *arg);

//一个简单的windows下的多线程程序
//使用WaitForSingleObject函数解决thread1的问题

int main(int argc, char *argv[])
{
	HANDLE hTread;
	DWORD wr;
	unsigned threadID;
	int param = 5;
	hTread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)&param, 0, &threadID); //创建一个新线程
	if ((wr = WaitForSingleObject(hTread, INFINITE)) == WAIT_FAILED)
	{
		puts("thread wait error");
		exit(1);
	}
	printf("wait result :%s\n", (wr == WAIT_OBJECT_0) ? "signaled" : "time-out");
	return 0;

}

unsigned WINAPI ThreadFunc(void *arg)
{
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; ++i)
	{
		Sleep(1000);
		puts("running thread");
	}
	return 0;
}