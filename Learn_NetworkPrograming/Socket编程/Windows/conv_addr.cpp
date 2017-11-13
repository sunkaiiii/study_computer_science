#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	/*inet_nota函数调用实例*/
	struct sockaddr_in addr;
	char strBuf[20];
	char strArr[20];

	addr.sin_addr.s_addr = htonl(0x10203040);
	//strPtr = inet_ntoa(addr.sin_addr); //inet_ntoa不建议使用，编译无法通过
	inet_ntop(AF_INET, &addr.sin_addr, strBuf, sizeof(strBuf));
	//strcpy(strArr, strPtr); 此方法不建议使用，编译不通过
	strcpy_s(strArr, strBuf);

	printf("Dotted_decimal notation3 %s\n", strArr);

	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}