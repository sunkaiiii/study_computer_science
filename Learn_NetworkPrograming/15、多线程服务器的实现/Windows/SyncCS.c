#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void *arg);
unsigned WINAPI threadDes(void  *arg);
 
//基于用户模式的CRITICAL_SECTION的同步方法
//实现了类似Linux下Mutex的机制

long long num = 0;
CRITICAL_SECTION cs;

int main(void)
{
	HANDLE tHandles[NUM_THREAD];
	int i;

	printf("sizeof long long: %d\n", sizeof(long long));

	InitializeCriticalSection(&cs);
	for (i = 0; i < NUM_THREAD; i++)
	{
		if (i % 2)
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadInc, NULL, 0, NULL);
		else
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadDes, NULL, 0, NULL);
	}
	WaitForMultipleObjects(NUM_THREAD, tHandles, TRUE, INFINITE);
	printf("result:%lld\n", num);
	DeleteCriticalSection(&cs);
	return 0;
}

unsigned WINAPI threadInc(void *arg)
{
	int i;
	EnterCriticalSection(&cs);
	for (i = 0; i < 50000000; i++)
		num += 1;
	LeaveCriticalSection(&cs);
	return 0;
}

unsigned WINAPI threadDes(void *arg)
{
	int i;
	EnterCriticalSection(&cs);
	for (i = 0; i < 50000000; i++)
		num -= 1;
	LeaveCriticalSection(&cs);
	return 0;
}