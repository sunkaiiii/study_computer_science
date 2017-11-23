#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);
#define BUF_SIZE 30

//因为Windows操作系统没有信号量
//所以处理MSG_OOB选用select来替代

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage <port>\n");
		exit(1);
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	SOCKET hAcptSock,hRecvSock;
	SOCKADDR_IN recvAdr, sendAdr;
	TIMEVAL timeout;
	fd_set reads, except,readCopy,exceptCopy;
	int sendAdrSize;
	int strLen, result;
	char buf[BUF_SIZE];
	hAcptSock = socket(PF_INET, SOCK_STREAM, 0);
	ZeroMemory(&recvAdr,0);
	recvAdr.sin_family = AF_INET;
	recvAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	recvAdr.sin_port = htons(atoi(argv[1]));
	if (bind(hAcptSock, (SOCKADDR*)&recvAdr, sizeof(recvAdr)) == -1)
		ErrorHandling("bind() error");
	if (listen(hAcptSock, 5) == -1)
		ErrorHandling("listen() error");
	sendAdrSize = sizeof(sendAdr);
	hRecvSock = accept(hAcptSock, (SOCKADDR*)&sendAdr, &sendAdrSize);
	FD_ZERO(&reads);
	FD_ZERO(&except);
	FD_SET(hRecvSock, &reads);
	FD_SET(hRecvSock, &except);
	while (1)
	{
		readCopy = reads;
		exceptCopy = except;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;
		if ((result = select(0, &readCopy, 0 ,&exceptCopy, &timeout)) == SOCKET_ERROR)
			break;
		if (result == 0)
		{
			continue;
		}
		if (result > 0)
		{
			if (FD_ISSET(hRecvSock, &exceptCopy))
			{
				strLen = recv(hRecvSock, buf, BUF_SIZE, MSG_OOB);
				buf[strLen] = 0;
				printf("Urgent Message  %s \n", buf);
			}
			if (FD_ISSET(hRecvSock, &readCopy))
			{
				strLen = recv(hRecvSock, buf, BUF_SIZE - 1, 0);
				if (strLen == 0)
				{
					break;
					closesocket(hRecvSock);
				}
				else
				{
					buf[strLen] = 0;
					puts(buf);
				}
			}
		}
		
	}
	closesocket(hAcptSock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}