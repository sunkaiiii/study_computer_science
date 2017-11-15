#define _WINSOCK_DEPRECATED_NO_WARNINGS

/*
Windows下需要调用getaddrinfo 
实在是懒得改了，就用define允许使用旧方法了
*/

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
	struct hostent *host;
	host = gethostbyname(argv[1]);
	if (!host)
		ErrorHandling("gethost...error");
	printf("Official name:%s\n", host->h_name);
	for (int i = 0; host->h_aliases[i]; ++i)
		printf("Aliases %d:%s \n", i + 1, host->h_aliases[i]);
	printf("Address type : %s \n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
	for (int i = 0; host->h_addr_list[i]; ++i)
		printf("IP addr %d: %s \n", i + 1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	WSACleanup();
	return 0;

}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}