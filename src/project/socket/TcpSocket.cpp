/*
 * ===========================================
 * File:   TcpSocket.cpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */

#include "TcpSocket.hpp"
#include "Error.hpp"

#define MAXPENDING 10
#define DEBUG

TcpSocket::TcpSocket()
{

}

TcpSocket::~TcpSocket()
{
	close(messageSocket);
	close(listenSocket);
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
	if ((listenSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		error("socket() failed");
		socketStatus = TcpSocket::CREATE_FAILED;
	}
}

void TcpSocket::bind(void)
{
#ifdef DEBUG
printf("Binding socket...\n");
#endif

	memset(&localHostAddress, 0, sizeof(localHostAddress));   	/* Zero out structure */
    localHostAddress.sin_family = AF_INET;                		/* Internet address family */
    localHostAddress.sin_addr.s_addr = htonl(INADDR_ANY); 		/* Any incoming interface */
    localHostAddress.sin_port = htons(getLocalPort());  		/* Local port */

    if (::bind(listenSocket, (struct sockaddr *) &localHostAddress, sizeof(localHostAddress)) < 0)
    {
    	error("bind() failed");
    	socketStatus = TcpSocket::BIND_FAILED;
    }
}
void TcpSocket::connect(char* remoteAddress)
{
#ifdef DEBUG
printf("Connecting to socket...\n");
#endif
	memset(&remoteHostAddress, 0, sizeof(remoteHostAddress));     	/* Zero out structure */
    remoteHostAddress.sin_family      = AF_INET;             		/* Internet address family */
    remoteHostAddress.sin_addr.s_addr = inet_addr(remoteAddress);   /* Server IP address */
    remoteHostAddress.sin_port        = htons(getRemotePort()); 	/* Server port */

    /* Establish the connection to the server */
    if (::connect(listenSocket, (struct sockaddr *) &remoteHostAddress, sizeof(remoteHostAddress)) < 0)
    {
    	error("connect() failed");
    	socketStatus = TcpSocket::CONNECT_FAILED;
    }
    else
    {
    	socketStatus = TcpSocket::CONNECTION_OK;
    }
    messageSocket = listenSocket; /* For send recv functions compatibility*/
}

void TcpSocket::listen(void)
{
#ifdef DEBUG
printf("Listening for connections...\n");
#endif
	if (::listen(listenSocket, MAXPENDING) < 0)
	{
		error("listen() failed");
		socketStatus = TcpSocket::LISTEN_FAILED;
	}
}


void TcpSocket::accept(void (*callbackForHandlingConnection)(void))
{
#ifdef DEBUG
printf("Accepting connection...\n");
#endif

	/* Set the size of the in-out parameter */
	remoteAddressLength = sizeof(remoteHostAddress);

	/* Wait for a client to connect */
	if ((messageSocket = ::accept(listenSocket, (struct sockaddr *) 0, 0)) < 0)
	{
		error("accept() failed");
		socketStatus = TcpSocket::ACCEPT_FAILED;
	}
	callbackForHandlingConnection();
}

void TcpSocket::send(message &dataBuffer)
{
	if (::send(messageSocket, &dataBuffer, sizeof(dataBuffer), 0) < 0)
	{
		error("send() failed");
		socketStatus = TcpSocket::SEND_FAILED;
	}
}

void TcpSocket::recv(message &dataBuffer, unsigned short &dataSize)
{
    if ((dataSize = ::recv(messageSocket, &dataBuffer, sizeof(dataBuffer), MSG_WAITALL)) < 0)
    {
    	error("recv() failed"); //MSG_WAITALL
    	socketStatus = TcpSocket::RECIEVE_FAILED;
    }
}

void TcpSocket::send(void)
{
	if (::send(messageSocket, &msg, sizeof(msg), 0) < 0)
	{
		error("send() failed");
		socketStatus = TcpSocket::SEND_FAILED;
	}
}

void TcpSocket::recv(void)
{
    if ((msgSize = ::recv(messageSocket, &msg, sizeof(msg), MSG_WAITALL)) < 0)
    {
    	error("recv() failed"); //MSG_WAITALL
    	socketStatus = TcpSocket::RECIEVE_FAILED;
    }
}

char* TcpSocket::getRemoteAddress(void)
{
	return inet_ntoa(remoteHostAddress.sin_addr);
}



