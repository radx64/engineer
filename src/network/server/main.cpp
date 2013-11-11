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

bool running = true;

void sigpipeIgnore(int signalnum)
{
	printf("Sigpipe caugth\n");
}

void sigInterruptHandle(int sigalnum)
{
	running = false;
}

void handleConnection()
{
	unsigned short size;
	while(running)
	{
		printf("Waiting for data\n");
		tcpsocket.recv(tcpsocket.msg,size);
		if(0 == size)
		{
			printf("Connection is closing by remote host...\n");
			break;
		}
		printf("Got message %s\nSending response...\n",tcpsocket.msg.data);
		sprintf(tcpsocket.msg.data,"Nothing yet implemented!");
		tcpsocket.send(tcpsocket.msg);
	}
}

/**
 * TCP server for data other than Voice like RS232 communication etc.
 */
void* createTCPThread(void* _arg)
{
	tcpsocket.setLocalPort(5000);
	tcpsocket.create();
	tcpsocket.bind();
	tcpsocket.listen();
	while(running)
	{
		tcpsocket.accept(handleConnection);
	}
	printf("Ending TCP Thread\n");
	return (void*)NULL;
}

/**
 * SIP server accepting calls from clients
 */
void* createVOIPThread(void* _arg)
{
	while(running)
	{
		voipPhone.loop();
		ms_usleep(50000);
	}
	printf("Ending VOIP Thread\n");
	voipPhone.terminate();
	return (void*)NULL;
}

int main(int argc, char* argv[])
{
	printf("Hello World in Server\n");
	signal(SIGPIPE, sigpipeIgnore);
	signal(SIGINT, sigInterruptHandle);
	pthread_t id[2];
	pthread_create(&id[0], NULL, createTCPThread, NULL);
	pthread_create(&id[1], NULL, createVOIPThread, NULL);
	while(running)
	{
		sleep(1);
	}
	printf("Ending main Thread\n");
	return 0;
}
