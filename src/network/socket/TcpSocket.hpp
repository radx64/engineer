#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MSG_SIZE 32

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
    void accept(void (*callbackForHandlingConnection)(int));
    void recv(char* dataBuffer, unsigned short &dataSize);
    void send(char* dataBuffer, unsigned short dataSize);

private:
	char dataBuffer[MSG_SIZE];
    int localSocketDescriptor;                    /* Socket descriptor for server */
    int remoteSocketDescriptor;                    /* Socket descriptor for client */
    struct sockaddr_in localHostAddress; /* Local address */
    struct sockaddr_in remoteHostAddress; /* Client address */
    unsigned short localPort;     		/* Server port */
    unsigned short remotePort;
    unsigned int remoteAddressLength;            /* Length of client address data structure */
};
