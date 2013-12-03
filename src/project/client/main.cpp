#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "../socket/TcpSocket.hpp"

void handleConnection(int desc)
{
	printf("Connection accepted and should be handled here");
}

int main(int argc, char* argv[])
{
	printf("Hello World in Client\n");
	char address[] = "127.0.0.1";
	TcpSocket tcpsocket;
	tcpsocket.msg.type = 1;
	tcpsocket.setRemotePort(5000);
	tcpsocket.create();
	tcpsocket.connect(address);
	while(1)
	{
		char buf[32];
		scanf("%s",buf);
		sprintf(tcpsocket.msg.data,"%s",buf);
		tcpsocket.send(tcpsocket.msg);
		unsigned short size;
		tcpsocket.recv(tcpsocket.msg,size);
		printf("Recived %d bytes of answer %s from server\n",size,tcpsocket.msg.data);
	}
	return 0;
}
