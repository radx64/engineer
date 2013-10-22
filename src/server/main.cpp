#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>

#include "server.cc"



/**
 * TCP server for data other than Voice like RS232 communication etc.
 */
void* createTCPThread(void* _arg)
{
	printf("Network not fully implemented yet!\n");

	  LOG_INFO << "pid = " << getpid();

	    EventLoop loop;
	    uint16_t port = static_cast<uint16_t>(9090);
	    InetAddress serverAddr(port);
	    ChatServer server(&loop, serverAddr);
	    server.start();
	    loop.loop();


	return (void*)NULL;
}

/**
 * SIP server accepting calls from clients
 */
void* createVOIPThread(void* _arg)
{
	printf("Sound input not implemented yet!\n");
	return (void*)NULL;
}

int main(int argc, char* argv[])
{
	printf("%s\n","Hello World from server!");
	pthread_t id[2];
	pthread_create(&id[0], NULL, createTCPThread, NULL);
	pthread_create(&id[1], NULL, createVOIPThread, NULL);
	sleep(2);
	void *end;
	for(int i=0;i<2;++i)
	{
		pthread_join(id[i], &end);
	}
	return 0;
}
