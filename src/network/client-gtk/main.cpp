#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "Window.h"

int main(int argc, char* argv[])
{
	printf("Hello World in Client\n");
	char address[] = "127.0.0.1";
	TcpSocket tcpsocket;
	tcpsocket.msg.type = 1;
	tcpsocket.setRemotePort(5000);
	tcpsocket.create();
	tcpsocket.connect(address);
	Gtk::Main kit(argc, argv);
	Window window (&tcpsocket);
	Gtk::Main::run(window);

	while(1)
	{
		//char buf[32];
		//scanf("%s",buf);
		//sprintf(tcpsocket.msg.data,"%s",buf);
		//tcpsocket.send(tcpsocket.msg);
		//unsigned short size;
		//tcpsocket.recv(tcpsocket.msg,size);
		//printf("Recived %d bytes of answer %s from server\n",size,tcpsocket.msg.data);
		sleep(1);
	}
	return 0;
}
