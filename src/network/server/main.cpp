#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "../socket/TcpSocket.hpp"
#include "../socket/MsgTypes.h"
#include "../voip/VoipPhone.hpp"

#define TCPPORT 	5000
#define SOCATPORT 	5100
#define VOIPPORT 	9999


TcpSocket tcpsocket;
VoipPhone voipPhone(VOIPPORT);

bool running = true;

void sigpipeIgnore(int signalnum)
{
	printf("Sigpipe caugth\n");
}

void sigInterruptHandle(int sigalnum)
{
	running = false;
}

unsigned short state[30] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};

void setGPIOstatus(unsigned short number, unsigned short value)
{
	 state[number] = value;
}
unsigned short getGPIOstatus(unsigned short number)
{
	return state[number]%2;
}


void GPIO_GEThandler(message &m)
{
	char buffer[2] = {tcpsocket.msg.data[0],tcpsocket.msg.data[1]};
	unsigned short pin = atoi(buffer);
	sprintf(tcpsocket.msg.data,"%02u %u", pin, getGPIOstatus(pin));
}

void GPIO_SEThandler(message &m)
{
	char buffer[2] = {tcpsocket.msg.data[0],tcpsocket.msg.data[1]};
	char buffer2[2] = {'0',tcpsocket.msg.data[3]};	//little dirty hack to fix atoi converstion problem;
	unsigned int pin = atoi(buffer);
	unsigned int value = atoi(buffer2);
	printf("Need to set %u to value %u\n",pin,value);
	setGPIOstatus(pin, value);
	sprintf(tcpsocket.msg.data,"%02u %u", pin, getGPIOstatus(pin));
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
	tcpsocket.setLocalPort(TCPPORT);
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
		/*
		char connection[64];
	   	sprintf(connection,"TCP-LISTEN:%d,fork", SOCATPORT);
		char* argv[] = { "socat","-d", "-d", "-d", connection, "/dev/pts/1,raw", NULL };	//run socat and create virtual serial port and add symlink in current directory
		printf("Forked socat... \n");
	   	execvp(argv[0], argv);
	   	while(true)
	   	{
	   		sleep(1);
	   	}
	   	*/
	}
	return 0;
}
