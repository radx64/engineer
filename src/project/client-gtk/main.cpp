/*
 * ===========================================
 * File:   main.cpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */

#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"
#include "Window.hpp"
#include "ConnectWindow.hpp"
#include <unistd.h>
#include <pthread.h>

VoipPhone voipPhone(19998);

void* voipLoop(void* _arg)
{
	//Window *window;
	//window = (Window *) _arg;

	return (void*)NULL;
}

void* createGUI(void* _arg)
{
	TcpSocket *sock;
	sock = (TcpSocket *) _arg;
	Window window (sock);
	Gtk::Main::run(window);
}

int main(int argc, char* argv[])
{

		TcpSocket tcpsocket;
		pthread_t VoipLoopThread;
		Gtk::Main kit(argc, argv);
		bool connectionSuccesfull = false;
		ConnectWindow connectWindow (&tcpsocket, &voipPhone, &connectionSuccesfull);
		Gtk::Main::run(connectWindow);
		printf("Connect Window closed!\n");
		if(connectionSuccesfull)
		{
			if (fork() != 0)		//fork for socat
			{
				voipPhone.loop();
				voipPhone.makeCall("sip:radek@192.168.1.104");
				voipPhone.loop();
				pthread_create(&VoipLoopThread, NULL, createGUI, (void*) &tcpsocket);
				while(1)
				{
					voipPhone.loop();
					//window->setVoipLatencyLabel("22");
					sleep(1);
				}

			}
			else
			{
				char connection[64];
		       	sprintf(connection,"tcp:%s:%d", tcpsocket.getRemoteAddress(),tcpsocket.getRemotePort()+1);
				char* argv[] = { "socat", "-d", "-d", "pty,link=./vcom1,echo=0,crnl",connection, NULL };	//run socat and create virtual serial port and add symlink in current directory
		       	execvp(argv[0], argv);

			}
	}

	return 0;
}
