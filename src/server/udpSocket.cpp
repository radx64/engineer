/*
 * udpSocket.cpp
 *
 *  Created on: 13 paź 2013
 *      Author: radek
 */

#include "udpSocket.hpp"

udpSocket::udpSocket() {
	// TODO Auto-generated constructor stub
	this->port = 5000;

}

udpSocket::~udpSocket() {
	// TODO Auto-generated destructor stub
}

bool udpSocket::createSocket(void)
{
	socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket_id < 0) return false;
	localAddressSize = sizeof(localAddress);
    memset((char *) &localAddress, 0, localAddressSize);
    localAddress.sin_family = AF_INET;
    localAddress.sin_port = htons(this->port);
    localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    					//cast below is smashing stack (need to be casted in another way)
    if (bind(socket_id, reinterpret_cast<const sockaddr*>(&localAddress), localAddressSize)==-1)
    {
    	perror("Couldn't bind port");
    }
    return true;
}

void udpSocket::receiveData(message &buffer, int &size, sockaddr_in &remoteAddress)
{

	remoteAddressSize = sizeof(remoteAddress);
	int receive = recvfrom(socket_id, &buffer, size, 0, reinterpret_cast<sockaddr*>(&remoteAddress), reinterpret_cast<socklen_t*>(&remoteAddressSize));
}
