#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);

#define BUF_SIZE 30

//一个简单的多播程序发送端
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
	SOCKET send_sock;
	struct sockaddr_in mul_adr;
	FILE *fp;
	char buf[BUF_SIZE];
	send_sock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&mul_adr, 0, sizeof(mul_adr));
	mul_adr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &mul_adr.sin_addr);
	mul_adr.sin_port = htons(atoi(argv[2]));

	fopen_s(&fp, "news_sender.c", "r");
	if (fp == NULL)
		ErrorHandling("fopen() error");
	while (!feof(fp))
	{
		fgets(buf, BUF_SIZE, fp);
		sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_adr, sizeof(mul_adr));
		Sleep(1000);
	}
	fclose(fp);
	closesocket(send_sock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}