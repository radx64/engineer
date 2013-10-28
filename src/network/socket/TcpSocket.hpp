#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */


class TcpSocket
{
public:
	TcpSocket();
	~TcpSocket();
	void setLocalPort(unsigned short port);
	unsigned short getLocalPort(void);

private:

    int localSocketDescriptor;                    /* Socket descriptor for server */
    int remoteSocketDescriptor;                    /* Socket descriptor for client */
    struct sockaddr_in localHostAddr; /* Local address */
    struct sockaddr_in remoteHostAddr; /* Client address */
    unsigned short localPort;     		/* Server port */
    unsigned int remoteAddressLength;            /* Length of client address data structure */

    void create(void);
    void bind(void);
    void listen(void);
};
