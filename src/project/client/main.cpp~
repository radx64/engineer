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
	char buffer[6] = "abcde";
	char address[] = "127.0.0.1";
	TcpSocket tcpsocket;
	tcpsocket.setRemotePort(5000);
	tcpsocket.create();
	tcpsocket.connect(address);
	tcpsocket.send(buffer,6);
	printf("Hello World in Client\n");
	return 0;
}
