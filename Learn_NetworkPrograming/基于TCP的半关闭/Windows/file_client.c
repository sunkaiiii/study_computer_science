#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 30
void ErrorHandling(char *message);
//接受文件的客户端，省略了一些错误判断
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
	FILE *fp;
	SOCKADDR_IN servAdr;
	char buf[BUF_SIZE];
	int strLen;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servAdr.sin_addr);
	servAdr.sin_port = htons(atoi(argv[2]));
	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	fopen_s(&fp,"receive.dat", "wb"); //vs2017下调用fopen编译不成功（需要声明用旧式函数或者用fopen_s);
	while (recv(sock, buf, BUF_SIZE, 0) != 0)
	{
		fwrite(buf, BUF_SIZE, 1, fp);
	}
	send(sock, "Thank you!", sizeof("Thank you!"),0);
	fclose(fp);
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