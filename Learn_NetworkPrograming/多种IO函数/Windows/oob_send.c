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
	SOCKET hSocket;
	SOCKADDR_IN sendAdr;
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	ZeroMemory(&send, 0);
	sendAdr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sendAdr.sin_addr);
	sendAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&sendAdr, sizeof(sendAdr)) == -1)
		ErrorHandling("connect() error");

	send(hSocket, "123", 3, 0);
	send(hSocket, "4", 1, MSG_OOB);
	send(hSocket, "567", 3, 0);
	send(hSocket, "890", 3, MSG_OOB);

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