#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);

//一个第四章缺陷回声客户端的改进版
//偷懒，省略了很多异常处理
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	if (argc != 3)
	{
		printf("Usage :%s  <IP> <port>\n", argv[0]);
		exit(1);
	}

	SOCKET hSocket;
	SOCKADDR_IN sendAdr;
	char message[BUF_SIZE];
	int strLen, readLen;

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	ZeroMemory(&sendAdr, sizeof(sendAdr));
	sendAdr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sendAdr.sin_addr);
	sendAdr.sin_port = htons(atoi(argv[2]));

	connect(hSocket, (SOCKADDR*)&sendAdr, sizeof(sendAdr));

	while (1)
	{
		fputs("input message (q to quit):", stdout);
		fgets(message, BUF_SIZE, stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;
		strLen = strlen(message);
		send(hSocket, message, strLen, 0);
		readLen = 0;
		while (1)
		{
			readLen += recv(hSocket, &message[readLen], BUF_SIZE - 1, 0);
			if (readLen >= strLen)
				break;
		}
		message[strLen] = '\0';
		printf("Message from server:%s\n", message);
	}
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

