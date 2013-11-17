#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include "MsgTypes.h"

#define MAX_MSG_SIZE 128

typedef struct
{
	int type;
	char size;	//size of data if data is transmited;
	char data[MAX_MSG_SIZE];
} message;


class TcpSocket
{
public:
	TcpSocket();
	~TcpSocket();
	void setLocalPort(unsigned short port);
	unsigned short getLocalPort(void);
	void setRemotePort(unsigned short port);
	unsigned short getRemotePort(void);
    void create(void);
    void bind(void);
    void connect(char* remoteAddress);
    void listen(void);
    void accept(void (*callbackForHandlingConnection)(void));
    void recv(message &dataBuffer, unsigned short &dataSize);
    void send(message &dataBuffer);
    message msg;

private:
    int listenSocket;                 	/* Socket descriptor for server */
    int messageSocket;                	/* Socket descriptor for client */
    struct sockaddr_in localHostAddress; 		/* Local address */
    struct sockaddr_in remoteHostAddress; 		/* Client address */
    unsigned short localPort;     				/* Server port */
    unsigned short remotePort;
    unsigned int remoteAddressLength;            /* Length of client address data structure */
};
#endif  /*  TCPSOCKET_H */
