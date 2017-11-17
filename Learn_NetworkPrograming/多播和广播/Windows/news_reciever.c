#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
#include<stdlib.h>
void ErrorHandling(char *message);

#define BUF_SIZE 30

//一个简单的多播程序接受端
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

	SOCKET recv_sock;
	int str_len;
	char buf[BUF_SIZE];
	struct sockaddr_in adr;
	struct ip_mreq join_adr;
	recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = htonl(INADDR_ANY);
	adr.sin_port = htons(atoi(argv[2]));

	inet_pton(AF_INET, argv[1], &join_adr.imr_multiaddr);
	join_adr.imr_interface.s_addr = htonl(INADDR_ANY);

	if (bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr)) == -1)
		ErrorHandling("bind() error");

	setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&join_adr, sizeof(join_adr));

	while (1)
	{
		str_len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);
		if (str_len<0)
			break;
		buf[str_len] = '\0';
		fputs(buf, stdout);
	}
	closesocket(recv_sock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}