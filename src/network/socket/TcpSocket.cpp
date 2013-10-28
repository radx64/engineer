#include "TcpSocket.hpp"

TcpSocket::TcpSocket()
{

}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::setLocalPort(unsigned short port)
{
	this->localPort = port;
}

unsigned short TcpSocket::getLocalPort(void)
{
	return this->localPort;
}

void TcpSocket::create(void)
{
    if ((this->localSocketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) throw "socket() failed";
}
