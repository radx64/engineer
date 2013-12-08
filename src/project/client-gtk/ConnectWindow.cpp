/*
 * ===========================================
 * File:   ConnectWindow.cpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */

#include "ConnectWindow.hpp"

ConnectWindow::ConnectWindow(TcpSocket *socketPtr, VoipPhone *voipPtr, bool *connectionSuccesfull)
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Table(3,2,true),
  socket(socketPtr),
  voip(voipPtr),
  connected(connectionSuccesfull)
{
  set_size_request(500, 200);
  set_title("Amateur Radio Remote Controller Client");

  //Signals attach
  m_ConnectButton.signal_clicked().connect( sigc::mem_fun(*this, &ConnectWindow::on_connect_clicked) );

  //Layout
  m_ConnectionFrame.set_shadow_type(Gtk::SHADOW_IN);
  m_ConnectionFrame.set_label("Connection settings:");
  m_ConnectionFrame.set_border_width(5);
  add(m_ConnectionFrame);

  m_ServerIPLabel.set_text("Server IP:");
  m_SIPPortLabel.set_text("SIP Port:");
  m_TCPPortLabel.set_text("TCP Port:");
  m_Table.set_border_width(5);
  m_Table.attach(m_ServerIPLabel,0,1,0,1);
  m_Table.attach(m_ServerIPEntry,1,2,0,1);
  m_Table.attach(m_SIPPortLabel,0,1,1,2);
  m_Table.attach(m_SIPPortEntry,1,2,1,2);
  m_Table.attach(m_TCPPortLabel,0,1,2,3);
  m_Table.attach(m_TCPPortEntry,1,2,2,3);
  m_VBox.pack_start(m_Table);
  m_ConnectButton.set_label("Connect to server");
  m_ConnectButton.set_can_default();
  m_ConnectButton.grab_default();
  m_VBox.pack_end(m_ConnectButton);
  m_VBox.set_border_width(5);
  m_ConnectionFrame.add(m_VBox);
  show_all_children();

}

ConnectWindow::~ConnectWindow()
{
}

void ConnectWindow::on_connect_clicked()
{
	socket->setRemotePort(atoi( m_TCPPortEntry.get_text().c_str()));
	socket->msg.type = 1;
	socket->create();
	socket->connect((char*)  m_ServerIPEntry.get_text().c_str());
	if(socket->socketStatus  != TcpSocket::CONNECTION_OK)
	{
		*connected = false;
		Gtk::MessageDialog dialog(*this, "Could not connect to server",false, Gtk::MESSAGE_ERROR);
		dialog.set_secondary_text("Check IP address and ports configuration.");
		dialog.run();
	}
	else
	{
		*connected = true;
	}
	voip->setPort(atoi(m_SIPPortEntry.get_text().c_str()));
	hide();
}
