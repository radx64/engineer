#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"
#include "Window.h"
#include "ConnectWindow.h"

VoipPhone voipPhone(9998);

int main(int argc, char* argv[])
{
	TcpSocket tcpsocket;
	Gtk::Main kit(argc, argv);
	bool connectionSuccesfull = false;
	//ConnectWindow connectWindow (&tcpsocket, &connectionSuccesfull);
	//Gtk::Main::run(connectWindow);
	//printf("Window closed!\n");
	//if(connectionSuccesfull)
	//{

	voipPhone.makeCall("sip:192.168.1.107:9999");
	while(1)
	{
		voipPhone.loop();
	}
	Window window (&tcpsocket);
	Gtk::Main::run(window);
	//}
	return 0;
}
