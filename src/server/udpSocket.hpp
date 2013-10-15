/*
 * udpSocket.h
 *
 *  Created on: 13 paź 2013
 *      Author: radek
 */

#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <time.h>

typedef struct {
    int type;
    int length;
    uint8_t buffer[512];
} message;


class udpSocket {
private:
	sockaddr_in localAddress, remoteAddress;
	int localAddressSize, remoteAddressSize;
	message data;
	int port;
	int socket_id;	//socket_id

public:
	udpSocket();
	virtual ~udpSocket();
	bool createSocket();
	void receiveData(message &buffer, int &size, sockaddr_in &remoteAddress);
	void sendData();
};

#endif /* UDPSOCKET_HPP_ */
