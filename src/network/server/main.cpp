#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "TcpSocket.hpp"


void handleConnection(int desc)
{
	printf("Connection accepted and should be handled here");
}

int main(int argc, char* argv[])
{
	TcpSocket tcpsocket;
	tcpsocket.setLocalPort(5000);
	tcpsocket.create();
	tcpsocket.bind();
	tcpsocket.listen();
	tcpsocket.accept(handleConnection);
	printf("Hello World in Client\n");
	return 0;
}
