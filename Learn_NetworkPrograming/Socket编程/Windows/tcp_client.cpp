#include<WinSock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<WS2tcpip.h> //里面包含着inet_pton
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	
	char message[30];
	int idx=0,readLen=0,strLen=0;
	if (argc != 3)
	{
		printf("Usage:%s <ip> <port> \n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup()  error");
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket(0 error");
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr(argv[1]); //此方法是个老方法，新版VS编译会报错，会提示推荐使用inet_pton
	if (inet_pton(AF_INET, argv[1], &servAddr.sin_addr) == WSAEFAULT)
		ErrorHandling("inet_pton error");
	servAddr.sin_port = htons(atoi(argv[2]));
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	while (readLen = recv(hSocket, &message[idx++], 1, 0))
	{
		if (readLen == -1)
			ErrorHandling("read() error!");
		strLen += readLen;
	}
	printf("Message from server:%s\n", message);
	printf("Function read call count:%d\n", strLen);
	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}