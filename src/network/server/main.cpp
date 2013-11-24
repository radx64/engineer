#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "../socket/TcpSocket.hpp"
#include "../socket/MsgTypes.h"
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

void GPIO_GEThandler(message &m)
{
	char buffer[2] = {tcpsocket.msg.data[0],tcpsocket.msg.data[1]};
	unsigned short pin = atoi(buffer);
	sprintf(tcpsocket.msg.data,"%02d 1", pin);
}

void GPIO_SEThandler(message &m)
{
	char buffer[2] = {tcpsocket.msg.data[0],tcpsocket.msg.data[1]};
	unsigned short pin = atoi(buffer);
	sprintf(tcpsocket.msg.data,"%02d 1", pin);
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

		printf("Got message: %s\n",tcpsocket.msg.data);

		switch (tcpsocket.msg.type)
		{
			case Msg::GPIO_GET : GPIO_GEThandler(tcpsocket.msg); break;
			case Msg::GPIO_SET : GPIO_SEThandler(tcpsocket.msg); break;
		}
		printf("Sending response: %s \n",tcpsocket.msg.data);
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
	if(fork() !=0)
	{
		while(running)
		{
			sleep(1);
		}
		printf("Ending main Thread\n");
	}
	else
	{
		char connection[64];
	   	sprintf(connection,"TCP-LISTEN:%d,fork", 5100);
		char* argv[] = { "socat","-d", "-d", "-d", connection, "/dev/pts/1,raw", NULL };	//run socat and create virtual serial port and add symlink in current directory
		printf("Forked socat... \n");
	   	execvp(argv[0], argv);
	   	while(true)
	   	{
	   		sleep(1);
	   	}
	}
	return 0;
}
