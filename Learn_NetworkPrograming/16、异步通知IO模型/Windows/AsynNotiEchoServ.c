#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);
#define BUF_SIZE 100

//利用异步通知I/O模型实现的回声服务器端
//从思路上来看比较像Windows版本的epoll

void CompressSockets(SOCKET hSockArr[], int index, int total);
void CompressEvents(WSAEVENT hEventArr[], int index, int total);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	if (argc != 2)
	{
		printf("Usage :%s <GroupIP> <port>\n", argv[0]);
		exit(1);
	}

	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;

	SOCKET hSockArr[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT hEventArr[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT newEvent;
	WSANETWORKEVENTS netEvents;

	int numofClntSock = 0;
	int strLen, i;
	int posInfo, startIndex;
	int clntAdrLen;
	char msg[BUF_SIZE];

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	ZeroMemory(&servAdr, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == -1)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == -1)
		ErrorHandling("listen() error");

	newEvent = WSACreateEvent();
	if (WSAEventSelect(hServSock, newEvent, FD_ACCEPT) == SOCKET_ERROR) //针对FD_ACCEPT事件调用了函数
		ErrorHandling("WSAEventSelect() error");

	//然后把函数连接的套接字和事件对象句柄分别存入hSockArr和hEventArr数组
	//同一个对象的套接字和事件应该保存在同一个索引（numofClntSock）当中
	hSockArr[numofClntSock] = hServSock; 
	hEventArr[numofClntSock] = newEvent;
	numofClntSock++;

	while (1)
	{
		posInfo = WSAWaitForMultipleEvents(numofClntSock, hEventArr, FALSE, WSA_INFINITE, FALSE);
		startIndex = posInfo - WSA_WAIT_EVENT_0;

		for (i = startIndex; i < numofClntSock; i++)
		{
			int sigEventIndex = WSAWaitForMultipleEvents(1, &hEventArr[i], TRUE, 0, FALSE);
			if ((sigEventIndex == WSA_WAIT_FAILED || sigEventIndex == WSA_WAIT_TIMEOUT))
				continue;
			else
			{
				sigEventIndex = i;
				WSAEnumNetworkEvents(hSockArr[sigEventIndex], hEventArr[sigEventIndex], &netEvents);
				if (netEvents.lNetworkEvents&FD_ACCEPT) //请求连接时
				{
					if (netEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						puts("Accept Error\n");
						break;
					}
					clntAdrLen = sizeof(clntAdr);
					hClntSock = accept(hSockArr[sigEventIndex], (SOCKADDR*)&clntAdr, &clntAdrLen);
					newEvent = WSACreateEvent();
					WSAEventSelect(hClntSock, newEvent, FD_READ | FD_CLOSE);
					hEventArr[numofClntSock] = newEvent;
					hSockArr[numofClntSock] = hClntSock;
					numofClntSock++;
					puts("connected new client");
				}
				if (netEvents.lNetworkEvents&FD_READ) //接收数据时
				{
					if (netEvents.iErrorCode[FD_READ_BIT] != 0)
					{
						puts("Read error\n");
						break;
					}
					strLen = recv(hSockArr[sigEventIndex], msg, sizeof(msg), 0);
					send(hSockArr[sigEventIndex], msg, strLen, 0);
				}
				if (netEvents.lNetworkEvents&FD_CLOSE) //断开连接请求
				{
					if (netEvents.iErrorCode[FD_CLOSE_BIT] != 0)
					{
						puts("Close error\n");
						break;
					}
					WSACloseEvent(hEventArr[sigEventIndex]);
					closesocket(hSockArr[sigEventIndex]);
					numofClntSock--;
					printf("client %d disconnected\n", hSockArr[sigEventIndex]);
					CompressSockets(hSockArr, sigEventIndex, numofClntSock);
					CompressEvents(hEventArr, sigEventIndex, numofClntSock);		
				}
			}
		}
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;

}

void CompressSockets(SOCKET hSockArr[], int index, int total)
{
	int i;
	for (i = index; i < total; i++)
		hSockArr[i] = hSockArr[i + 1];
}
void CompressEvents(WSAEVENT hEventArr[], int index, int total)
{
	int i;
	for (i = index; i < total; i++)
	{
		hEventArr[i] = hEventArr[i + 1];
	}
}


void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}