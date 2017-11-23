#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
void ErrorHandling(char *message);
#define BUF_SIZE 30
void ShowSocketBufSize(SOCKET sock);
int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	SOCKET hSock;
	int sndBuf, rcvBuf, state;
	hSock = socket(PF_INET, SOCK_STREAM, 0);
	ShowSocketBufSize(hSock);
	sndBuf = 1024 * 3;
	rcvBuf = 1024 * 3;
	state = setsockopt(hSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, sizeof(sndBuf));
	if (state == SOCKET_ERROR)
		ErrorHandling("getsockopt() error");
	state = setsockopt(hSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, sizeof(rcvBuf));
	if (state == SOCKET_ERROR)
		ErrorHandling("getsockopt() error");
	ShowSocketBufSize(hSock);
	closesocket(hSock);
	WSACleanup();
	return 0;

}

void ShowSocketBufSize(SOCKET sock)
{
	int sndBuf, rcvBuf, state, len;
	
	len = sizeof(sndBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
	if (state == SOCKET_ERROR)
		ErrorHandling("getsockopt() error");
	len = sizeof(rcvBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
	if (state == SOCKET_ERROR)
		ErrorHandling("getsockopt() error");
	printf("Input buffer size :%d\n", rcvBuf);
	printf("Output buffer size:%d\n", sndBuf);
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}