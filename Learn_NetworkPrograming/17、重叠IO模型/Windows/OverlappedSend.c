#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);


int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	if (argc != 3)
	{
		printf("Usage :%s <GroupIP> <port>\n", argv[0]);
		exit(1);
	}

	SOCKET hSocket;
	SOCKADDR_IN sendAdr;
	WSABUF dataBuf;
	char msg[] = "Network is computer!";
	int sendBytes = 0;

	WSAEVENT evobj;
	WSAOVERLAPPED overlapped;

	hSocket = WSASocketW(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);//FLAG_OVERLAPPED声明这个套接字是一个重叠IO的套接字
	ZeroMemory(&sendAdr, sizeof(sendAdr));
	sendAdr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sendAdr.sin_addr);
	sendAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&sendAdr, sizeof(sendAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	evobj = WSACreateEvent();
	ZeroMemory(&overlapped, sizeof(overlapped));
	overlapped.hEvent = evobj;
	dataBuf.len = strlen(msg) + 1;
	dataBuf.buf = msg;
	if (WSASend(hSocket, &dataBuf, 1, &sendBytes, 0, &overlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSA_IO_PENDING) //如果返回的是IO_PENDING，则表示并不是发生了错误，而是尚未完成（Pending）状态
		{
			puts("Background data send");
			WSAWaitForMultipleEvents(1, &evobj, TRUE, WSA_INFINITE, FALSE);
			WSAGetOverlappedResult(hSocket, &overlapped, &sendBytes, FALSE, NULL);
		}
		else
		{
			ErrorHandling("WSASend() error");
		}
	}
	printf("Send data size :%d", sendBytes);
	WSACloseEvent(evobj);
	closesocket(hSocket);
	WSACleanup();
	return 0;

}



void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

