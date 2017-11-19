#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void *arg);
unsigned WINAPI threadDes(void  *arg);
 
//基于内核模式的互斥量的同步方法

long long num = 0;
HANDLE mutex;

int main(void)
{
	HANDLE tHandles[NUM_THREAD];
	int i;

	printf("sizeof long long: %d\n", sizeof(long long));
	mutex = CreateMutex(NULL, FALSE, NULL);
	for (i = 0; i < NUM_THREAD; i++)
	{
		if (i % 2)
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadInc, NULL, 0, NULL);
		else
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadDes, NULL, 0, NULL);
	}
	WaitForMultipleObjects(NUM_THREAD, tHandles, TRUE, INFINITE);
	printf("result:%lld\n", num);
	CloseHandle(mutex);
	return 0;
}

unsigned WINAPI threadInc(void *arg)
{
	int i;
	WaitForSingleObject(mutex, INFINITE);
	for (i = 0; i < 50000000; i++)
		num += 1;
	ReleaseMutex(mutex);
	return 0;
}

unsigned WINAPI threadDes(void *arg)
{
	int i;
	WaitForSingleObject(mutex, INFINITE);
	for (i = 0; i < 50000000; i++)
		num -= 1;
	ReleaseMutex(mutex);
	return 0;
}