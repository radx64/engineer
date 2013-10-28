#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

/**
 * TCP server for data other than Voice like RS232 communication etc.
 */
void* createTCPThread(void* _arg)
{
	printf("Network not fully implemented yet!\n");

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
