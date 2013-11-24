#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"
#include "Window.h"
#include "ConnectWindow.h"
#include <unistd.h>

VoipPhone voipPhone(9998);

int main(int argc, char* argv[])
{

		TcpSocket tcpsocket;
		Gtk::Main kit(argc, argv);
		bool connectionSuccesfull = false;
		ConnectWindow connectWindow (&tcpsocket, &voipPhone, &connectionSuccesfull);
		Gtk::Main::run(connectWindow);
		printf("Connect Window closed!\n");
		if(connectionSuccesfull)
		{
			if (fork() != 0)		//fork for socat
			{
				//voipPhone.makeCall("sip:192.168.1.107:9999");
				//while(1)
				//{
					//voipPhone.loop();
				//}
				Window window (&tcpsocket);
				Gtk::Main::run(window);
			}
			else
			{
				char connection[64];

		       	sprintf(connection,"tcp:%s:%d", tcpsocket.getRemoteAddress(),(tcpsocket.getRemotePort()+10));
				char* argv[] = { "socat", "-d", "-d", "pty,link=./vcom1,echo=0,crnl",connection, NULL };	//run socat and create virtual serial port and add symlink in current directory
		       	execvp(argv[0], argv);

			}
	}

	return 0;
}
