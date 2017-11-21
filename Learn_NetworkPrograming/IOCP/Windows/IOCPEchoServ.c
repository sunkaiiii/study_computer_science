#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>
#include<process.h>

//基于IOCP的，即为简单普通的回声服务器端

#define BUF_SIZE 100
#define READ 3
#define WRITE 5

typedef struct //与客户端相连接的套接字结构体
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//将IO中使用的缓冲和重叠IO中需要的OVERLAPPED结构体封装在同一个结构体中
typedef struct  //buffer的信息
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char bufer[BUF_SIZE];
	int rwMode; //读取或写入
}PER_IO_DATA, *LPPER_IO_DATA;

void ErrorHandling(char *message);
DWORD WINAPI EchoThreadMain(LPVOID CompletionPortIO);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	HANDLE hComPort;
	SYSTEM_INFO sysInfo;
	LPPER_IO_DATA ioInfo;
	LPPER_HANDLE_DATA handleInfo;

	SOCKET hServSock;
	SOCKADDR_IN servAdr;
	int recvBytes, i, flags = 0;
	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0); //创建一个CP对象
	GetSystemInfo(&sysInfo);
	printf("当前电脑CPU核心数为:%d\n", sysInfo.dwNumberOfProcessors);
	for (i = 0; i < sysInfo.dwNumberOfProcessors; i++) //创建与当前电脑CPU核数相同的线程
	{
		_beginthreadex(NULL, 0, EchoThreadMain, (LPVOID)hComPort, 0, NULL);//传递cp对象句柄和线程，线程将通过该句柄访问cp对象
	}

	hServSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ZeroMemory(&servAdr, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	listen(hServSock, 5);

	while (1)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);

		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &addrLen);

		//动态分配PER_HANDLE_DATA结构体，写入客户端连接套接字以及客户端地址信息
		handleInfo = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		handleInfo->hClntSock = hClntSock;
		memcpy(&(handleInfo->clntAdr), &clntAdr, addrLen); 

		//连接创建的cp对象和创建的客户端套接字
		//针对该套接字的重叠io完成时，将写入连接的cp对象，引起GetQueue...函数的返回
		//要连接的套接字句柄、要连接的cp对象、传递已完成的套接字信息
		CreateIoCompletionPort((HANDLE)hClntSock, hComPort, (DWORD)handleInfo, 0);

		//动态分配PER_IO_DATA结构体变量，同时准备用于WSARecv函数中用的OVERLAPPED结构体变量，wsaBuf缓冲
		ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->bufer;
		ioInfo->rwMode = READ;
	
		//第七个变量传递了OVERLAPPED结构体的地址值，该值也可以在GetQueue...函数返回得到
		//结构体变量的地址值与第一个成员的地址值相同，实际上也就是传递了成哥PER_IO_DATA结构体
		WSARecv(handleInfo->hClntSock, &(ioInfo->wsaBuf), 1, &recvBytes, &flags, &(ioInfo->overlapped), NULL);
	}
	return 0;

}

DWORD WINAPI EchoThreadMain(LPVOID pComPort)
{
	//由线程运行EchoThreadMain函数，调用GetQueue，函数的线程就是分配各CP对象的线程
	HANDLE hComPort = (HANDLE)pComPort;
	SOCKET sock;
	DWORD bytesTrans;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA ioInfo;
	DWORD flags = 0;

	while (1)
	{
		//调用GetQueued，函数在IO完成且已注册相关信息时返回（最后一个参数是INFINITE）
		//返回时可以通过第三、第四个参数得到之前传递的结构体信息
		GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&handleInfo, (LPOVERLAPPED*)&ioInfo, INFINITE);
		sock = handleInfo->hClntSock;

		//检查rwMode成员中的值判断是输入完成还是输出完成
		if (ioInfo->rwMode == READ)
		{
			puts("message received!\n");
			if (bytesTrans == 0) //传递EOF的时候
			{
				closesocket(sock);
				free(handleInfo);
				free(ioInfo);
				printf("client disconnected : %d\n", sock);
				continue;
			}

			//将服务器接受到的值发送给客户端
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = bytesTrans;
			ioInfo->rwMode = WRITE;
			WSASend(sock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);
			ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->bufer;
			ioInfo->rwMode = READ;
			//发送信息之后接受客户端信息
			WSARecv(sock, &(ioInfo->wsaBuf), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
		}
		else
		{
			//完成IO为输出时执行else区域
			puts("message sent!\n");
			free(ioInfo);
		}
	}
	return 0;
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}