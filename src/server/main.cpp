#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "udpSocket.hpp"

void* create_network_thread(void* _arg)
{
	printf("Network not fully implemented yet!\n");
	udpSocket udp;
	if (!udp.createSocket()) perror("Couldn't create socket!");
	return (void*)NULL;
}

void* create_sound_input_thread(void* _arg)
{
	printf("Sound input not implemented yet!\n");
	return (void*)NULL;
}

void* create_sound_output_thread(void* _arg)
{
	printf("Sound output not implemented yet!\n");
	return (void*)NULL;
}	

int main(int argc, char* argv[])
{
	printf("%s\n","Hello World from server!");
	pthread_t id[3];
	pthread_create(&id[0], NULL, create_network_thread, NULL);
	pthread_create(&id[1], NULL, create_sound_input_thread, NULL);
	pthread_create(&id[2], NULL, create_sound_output_thread, NULL);
	sleep(2);
	void *end;
	for(int i=0;i<3;++i)
	{
		pthread_join(id[0], &end);
		pthread_join(id[1], &end);
		pthread_join(id[2], &end);
	}
	return 0;
}
