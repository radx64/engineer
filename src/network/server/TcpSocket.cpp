#include "TcpSocket.hpp"
#include "Error.hpp"

#define MAXPENDING 10
#define MSG_SIZE 32
#define DEBUG

TcpSocket::TcpSocket()
{

}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::setLocalPort(unsigned short port)
{
	localPort = port;
}

unsigned short TcpSocket::getLocalPort(void)
{
	return localPort;
}

void TcpSocket::setRemotePort(unsigned short port)
{
	remotePort = port;
}

unsigned short TcpSocket::getRemotePort(void)
{
	return remotePort;
}

void TcpSocket::create(void)
{
	#ifdef DEBUG
	printf("Creating socket...\n");
	#endif
	if ((localSocketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) error("socket() failed");
}

void TcpSocket::bind(void)
{
#ifdef DEBUG
printf("Binding socket...\n");
#endif

	memset(&localHostAddress, 0, sizeof(localHostAddress));   /* Zero out structure */
    localHostAddress.sin_family = AF_INET;                	/* Internet address family */
    localHostAddress.sin_addr.s_addr = htonl(INADDR_ANY); 	/* Any incoming interface */
    localHostAddress.sin_port = htons(getLocalPort());  /* Local port */

    if (::bind(localSocketDescriptor, (struct sockaddr *) &localHostAddress, sizeof(localHostAddress)) < 0) error("bind() failed");
}
void TcpSocket::connect(char* remoteAddress)
{
#ifdef DEBUG
printf("Connecting to socket...\n");
#endif
	memset(&remoteHostAddress, 0, sizeof(remoteHostAddress));     /* Zero out structure */
    remoteHostAddress.sin_family      = AF_INET;             /* Internet address family */
    remoteHostAddress.sin_addr.s_addr = inet_addr(remoteAddress);   /* Server IP address */
    remoteHostAddress.sin_port        = htons(getRemotePort()); /* Server port */

    /* Establish the connection to the echo server */
    if (::connect(localSocketDescriptor, (struct sockaddr *) &remoteHostAddress, sizeof(remoteHostAddress)) < 0) error("connect() failed");
}

void TcpSocket::listen(void)
{
#ifdef DEBUG
printf("Listening for connections...\n");
#endif
	if (::listen(localSocketDescriptor, MAXPENDING) < 0) error("listen() failed");
}


void TcpSocket::accept(void (*callbackForHandlingConnection)(int))
{
#ifdef DEBUG
printf("Accepting connection...\n");
#endif

	/* Set the size of the in-out parameter */
	remoteAddressLength = sizeof(remoteHostAddress);

	/* Wait for a client to connect */
	if ((remoteSocketDescriptor = ::accept(localSocketDescriptor, (struct sockaddr *) &remoteHostAddress, &remoteAddressLength)) < 0) error("accept() failed");
	callbackForHandlingConnection(remoteSocketDescriptor);
}

void TcpSocket::send(char* dataBuffer, unsigned short dataSize)
{
    if (::send(remoteSocketDescriptor, dataBuffer, dataSize, 0) != dataSize) error("send() failed");

}

void TcpSocket::recv(char* dataBuffer, unsigned short &dataSize)
{
    if ((dataSize = ::recv(remoteSocketDescriptor, dataBuffer, MSG_SIZE, 0)) < 0) error("recv() failed");
}




