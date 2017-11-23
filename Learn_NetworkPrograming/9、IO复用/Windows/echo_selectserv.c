#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);
#define BUF_SIZE 30
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
	SOCKET hServsock,hClntsock;
	SOCKADDR_IN servADr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;
	int adrSz;
	int strLen, fdNum, i;
	char buf[BUF_SIZE];
	hServsock = socket(PF_INET, SOCK_STREAM, 0);
	ZeroMemory(&servADr, 0);
	servADr.sin_family = AF_INET;
	servADr.sin_addr.s_addr = htonl(INADDR_ANY);
	servADr.sin_port = htons(atoi(argv[1]));
	if (bind(hServsock, (SOCKADDR*)&servADr, sizeof(servADr)) == -1)
		ErrorHandling("bind() error");
	if (listen(hServsock, 5) == -1)
		ErrorHandling("listen() error");
	FD_ZERO(&reads);
	FD_SET(hServsock, &reads);
	while (1)
	{
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;
		if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
			break;
		if (fdNum == 0)
		{
			printf("time out\n");
			continue;
		}
		for (i = 0; i < reads.fd_count; i++)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if (reads.fd_array[i] == hServsock) //连接请求
				{
					adrSz = sizeof(clntAdr);
					hClntsock = accept(hServsock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hClntsock, &reads);
					printf("connected client : %d\n", hClntsock);
				}
				else //读取数据请求
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE, 0);
					if (strlen == 0) //断开请求
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client:%d\n", cpyReads.fd_array[i]);
					}
					else
					{
						send(reads.fd_array[i], buf, strLen, 0);
					}
				}
			}
		}
	}
	closesocket(hServsock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}