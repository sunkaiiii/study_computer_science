#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 1024
void ErrorHandling(char *message);
void CALLBACK ReadCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK WriteComRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

//使用纯重叠IO模型实现回声服务器端，代码较多~
typedef struct
{
	SOCKET hClntSock;
	char buf[BUF_SIZE];
	WSABUF wsaBuf;
} PER_IO_DATA, *LPEER_IO_DATA;

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
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	LPWSAOVERLAPPED lpOvlp;
	DWORD recvBytes;
	LPEER_IO_DATA hbInfo;
	int mode = 1, recvAdrSz, flagInfo = 0;
	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); //申请一个重叠IO的套接字
	ioctlsocket(hLisnSock, FIONBIO, &mode); //当传入的数字不为0的时候，将会把套接字改为非阻塞模式

	ZeroMemory(&lisnAdr, sizeof(lisnAdr));
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == -1)
		ErrorHandling("bind() error");
	if (listen(hLisnSock, 5) == -1)
		ErrorHandling("listen() error");

	recvAdrSz = sizeof(recvAdr);
	while (1)
	{
		SleepEx(100, TRUE); //为了运行Completion Routine函数，需要循环调用SleepEx函数
		hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock == INVALID_SOCKET) //并且因为是非阻塞的，要处理INVALID_SOCKET的情况
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected\n");

		//重叠IO所需要的结构体初始化，因为每一个客户端都需要一个结构体
		//所以使用malloc进行动态分配
		lpOvlp = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));
		memset(lpOvlp, 0, sizeof(WSAOVERLAPPED));

		//动态分配PER_IO_DATA结构体内存空间，并向起写入套接字句柄
		hbInfo = (LPEER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo->hClntSock = (DWORD)hRecvSock;
		(hbInfo->wsaBuf).buf = hbInfo->buf;
		(hbInfo->wsaBuf).len = BUF_SIZE;

		//WSAOVERLAPPED结构体变量的event成员将写入之前分配的结构体变量
		//基于Completion Routine函数的重叠IO不需要时间对象
		//因此event事件里可以添加别的信息
		lpOvlp->hEvent = (HANDLE)hbInfo; 
		//调用WSARecv函数将ReadCompRoutine指定为Completion Routine
		//并将lpOvlp传递到函数中，CompletionRoutine韩式内可以访问完成IO的套接字句柄和缓冲
		WSARecv(hRecvSock, &(hbInfo->wsaBuf), 1, &recvBytes, &flagInfo, lpOvlp, ReadCompRoutine);
	}
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	return 0;

}
void CALLBACK ReadCompRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags) //该函数调用意味着完成了数据的输入，现在要发送数据给回升客户端
{
	LPEER_IO_DATA hbInfo = (LPEER_IO_DATA)(lpOverlapped->hEvent);
	SOCKET hSock = hbInfo->hClntSock;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	DWORD sendByes;

	if (szRecvBytes == 0) //断开请求
	{
		closesocket(hSock); 
		free(lpOverlapped->hEvent);
		free(lpOverlapped);
		puts("client disconnected\n");
	}
	else //回声数据
	{
		bufInfo->len = szRecvBytes;
		WSASend(hSock, bufInfo, 1, &sendByes, 0, lpOverlapped, WriteComRoutine); //继续利用WSASend发送重叠IO的Send
	}
}
void CALLBACK WriteComRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	LPEER_IO_DATA hbInfo = (LPEER_IO_DATA)(lpOverlapped->hEvent);
	SOCKET hSock = hbInfo->hClntSock;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	DWORD recvBytes;
	int flagInfo = 0;
	WSARecv(hSock, bufInfo, 1, &recvBytes, &flagInfo, lpOverlapped, ReadCompRoutine); //发送消息之后，服务器可以继续接受消息
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}