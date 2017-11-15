#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 30
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	SOCKET sock;
	char message[BUF_SIZE];
	SOCKADDR_IN servAdr;
	int strLen;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servAdr.sin_addr);
	servAdr.sin_port = htons(atoi(argv[2]));
	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));  //有连接的UDP
	while (1)
	{
		fputs("Insert Message(q to quit):", stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			break;
		}
		send(sock, message, strlen(message), 0); //因为是有连接的，所以用send替代sendto，recv替代recvfrom
		strLen = recv(sock, message, BUF_SIZE - 1, 0);
		message[strLen] = '\0';
		printf("Message from server:%s\n", message);
	}
	closesocket(sock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}