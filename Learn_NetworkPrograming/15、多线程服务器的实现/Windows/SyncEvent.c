#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define STR_LEN 100

//2个线程将同时等待输入字符串
//使用事件进行同步
//计算'A'和其他字符的数目

unsigned WINAPI NumberOfA(void *arg);
unsigned WINAPI NumberOfOthers(void *arg);

static char str[STR_LEN];
static HANDLE hEvent;

int main(void)
{
	HANDLE hThread1, hThread2;
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //第三个参数为FALSE，说明他是个初始状态为non_signaled的状态
	hThread1 = (HANDLE)_beginthreadex(NULL, 0, NumberOfA, NULL, 0, NULL);
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, NumberOfOthers, NULL, 0, NULL);

	fputs("Input string: ", stdout);
	fgets(str, STR_LEN, stdin);
	SetEvent(hEvent); //读入之后，将事件设置为signaled

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	ResetEvent(hEvent); //以防万一，重新将事件设置为non_signaled
	CloseHandle(hEvent);
	return 0;
}

unsigned WINAPI NumberOfA(void *arg)
{
	int i, cnt = 0;
	WaitForSingleObject(hEvent, INFINITE); //等待用户输入，对象状态改为signaled的那一刻
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'A')
			cnt++;
	}
	printf("Num of A :%d\n", cnt);
	return 0;
}

unsigned WINAPI NumberOfOthers(void *arg)
{
	int i, cnt = 0;
	WaitForSingleObject(hEvent, INFINITE);//等待用户输入，对象状态改为signaled的那一刻
	for (i = 0; str[i] != 0; i++)
	{
		if (str[i] != 'A')
			cnt++;
	}
	printf("Num of others:%d\n", cnt - 1);
	return 0;
}