#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"

TcpSocket tcpsocket;
VoipPhone voipPhone(9999);

void handleConnection()
{
	printf("Connection accepted and should be handled here\n");
	unsigned short size;
	while(1)
	{
		tcpsocket.recv(tcpsocket.msg,size);
		printf("Got message %s\nSending response...\n",tcpsocket.msg.data);
		sprintf(tcpsocket.msg.data,"Nothing yet!\n");
		tcpsocket.send(tcpsocket.msg);
	}
}

int main(int argc, char* argv[])
{
	printf("Hello World in Server\n");
	while(1)
	{
		voipPhone.loop();
		ms_usleep(50000);
	}
	voipPhone.terminate();

	tcpsocket.setLocalPort(5000);
	tcpsocket.create();
	tcpsocket.bind();
	tcpsocket.listen();
	tcpsocket.accept(handleConnection);
	return 0;
}
