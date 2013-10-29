#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "../socket/TcpSocket.hpp"

	TcpSocket tcpsocket;

void handleConnection()
{
	printf("Connection accepted and should be handled here\n");
	unsigned short size;
	while(1)
	{
		tcpsocket.recv(tcpsocket.msg,size);
		printf("Got message %s\nSending response...\n",tcpsocket.msg.data);
		sprintf(tcpsocket.msg.data,"Nothing yet!\n");
		tcpsocket.send(tcpsocket.msg,sizeof(tcpsocket.msg));
	}
}

int main(int argc, char* argv[])
{
	printf("Hello World in Server\n");
	tcpsocket.setLocalPort(5000);
	tcpsocket.create();
	tcpsocket.bind();
	tcpsocket.listen();
	tcpsocket.accept(handleConnection);
	return 0;
}
