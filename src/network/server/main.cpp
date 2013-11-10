#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"

TcpSocket tcpsocket;
VoipPhone voipPhone(9999);

void sigpipeIgnore()
{
	printf("Sigpipe caugth\n");
}

void handleConnection()
{
	printf("Connection accepted and should be handled here\n");
	unsigned short size;
	while(1)
	{
		printf("Waiting for data\n");
		tcpsocket.recv(tcpsocket.msg,size);
		printf("Got message %s\nSending response...\n",tcpsocket.msg.data);
		sprintf(tcpsocket.msg.data,"Nothing yet implemented!\n");
		tcpsocket.send(tcpsocket.msg);
	}
}

/**
 * TCP server for data other than Voice like RS232 communication etc.
 */
void* createTCPThread(void* _arg)
{
	printf("Network not fully implemented yet!\n");
	signal(SIGPIPE, SIG_IGN);
	tcpsocket.setLocalPort(5000);
	tcpsocket.create();
	tcpsocket.bind();
	tcpsocket.listen();
	while(1)
	{
		tcpsocket.accept(handleConnection);
	}
	return (void*)NULL;
}

/**
 * SIP server accepting calls from clients
 */
void* createVOIPThread(void* _arg)
{
	printf("Sound input not implemented yet!\n");
	while(1)
	{
		voipPhone.loop();
		ms_usleep(50000);
	}
	voipPhone.terminate();
	return (void*)NULL;
}

int main(int argc, char* argv[])
{
	printf("Hello World in Server\n");
	pthread_t id[2];
	pthread_create(&id[0], NULL, createTCPThread, NULL);
	pthread_create(&id[1], NULL, createVOIPThread, NULL);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
