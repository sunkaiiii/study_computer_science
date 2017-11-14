#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
void ErrorHandling(char *message);
#define BUF_SIZE 1024
#define OPSZ 4
int calculate(int opnum, int opnds[], char op);
int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	SOCKET hServSock, hClntSock;
	char opinfo[BUF_SIZE];
	int strLen,openCnt, i;
	int recvCnt, recvLen;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;
	if (argc != 2)
	{
		printf("Usage %s <port>\n", argv[0]);
		exit(1);
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	clntAdrSize = sizeof(clntAdr);

	for (int i = 0; i < 5; ++i)
	{
		openCnt = 0;
		char count[1];
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1)
			ErrorHandling("acept() error");
		recv(hClntSock, count, 1, 0);
		openCnt = (int)count[0];
		recvLen = 0;
		while ((openCnt*OPSZ + 1) > recvLen)
		{
			recvCnt = recv(hClntSock, opinfo, BUF_SIZE - 1, 0);
			recvLen += recvCnt;
		}
		int result = calculate(openCnt, (int*)opinfo, opinfo[recvLen - 1]);
		printf("%d\n", result);
		send(hClntSock, (char*)&result, sizeof(result), 0);
		closesocket(hClntSock);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;

}
int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;
	switch (op)
	{
	case '+':
		for (i = 1; i<opnum; ++i)
			result += opnds[i];
		break;
	case '-':
		for (i = 1; i<opnum; ++i)
			result -= opnds[i];
		break;
	case '*':
		for (i = 1; i<opnum; ++i)
			result *= opnds[i];
		break;
	}
	return result;
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}