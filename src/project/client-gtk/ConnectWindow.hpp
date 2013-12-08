/*
 * ===========================================
 * File:   ConnectWindow.hpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */
#ifndef GTKMM_CONNECTWINDOW_HPP_
#define GTKMM_CONNECTWINDOW_HPP_

#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"

class ConnectWindow : public Gtk::Window
{
public:
	ConnectWindow(TcpSocket *socketPtr, VoipPhone *voipPtr, bool *connectionSuccesfull);
	virtual ~ConnectWindow();

protected:
  //Signal handlers:
  void on_connect_clicked();

  Gtk::Frame m_ConnectionFrame;
  Gtk::Box m_VBox;
  Gtk::Table m_Table;
  Gtk::Label m_ServerIPLabel;
  Gtk::Entry m_ServerIPEntry;
  Gtk::Label m_SIPPortLabel;
  Gtk::Entry m_SIPPortEntry;
  Gtk::Label m_TCPPortLabel;
  Gtk::Entry m_TCPPortEntry;
  Gtk::Button m_ConnectButton;

  TcpSocket *socket;
  VoipPhone *voip;
  bool *connected;
};

#endif /* GTKMM_CONNECTWINDOW_HPP_ */





