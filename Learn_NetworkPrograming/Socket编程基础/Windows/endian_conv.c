#include<WinSock2.h>
#include<stdio.h>
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");


	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	net_port = htons(host_port); //host to net short
	net_addr = htonl(host_addr); //host to net long

	printf("Host odered port %#x \n", host_port);
	printf("Network odered port %#x \n", net_port);
	printf("Host odered adress %#x \n", host_addr);
	printf("Network odered adress %#x \n", net_addr);

	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}