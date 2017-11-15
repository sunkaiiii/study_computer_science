#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
void ErrorHandling(char *message);
#define BUF_SIZE 30
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage %s <port>\n", argv[0]);
		exit(1);
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	SOCKET hServSock, hClntSock;
	FILE *fp;
	char buf[BUF_SIZE];
	SOCKADDR_IN servAdr, clntAdr;
	int readCnt;
	//fp = fopen("file_server.c", "rb"); //vs2017下调用fopen编译不成功（需要声明用旧式函数或者用fopen_s);
	fopen_s(&fp,"file_server.c", "rb");
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));
	
	bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	listen(hServSock, 5);
	int clntAdrSz = sizeof(clntAdr);
	hClntSock=accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
	while (1)
	{
		readCnt = fread((void*)buf,1,BUF_SIZE,fp);
		if (readCnt < BUF_SIZE)
		{
			send(hClntSock, (char*)&buf, readCnt, 0);
			break;
		}
		send(hClntSock, (char*)&buf, BUF_SIZE, 0);
	}
	shutdown(hClntSock, SD_SEND);
	recv(hClntSock, (char*)buf, BUF_SIZE, 0);
	printf("Message from client: %s", buf);
	
	fclose(fp);
	closesocket(hServSock);
	closesocket(hClntSock);
	WSACleanup();
	return 0;

}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}