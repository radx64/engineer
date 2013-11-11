/*
 * Window.cpp
 *
 *  Created on: 11 lis 2013
 *      Author: radek
 */

#include "Window.h"

Window::Window(TcpSocket *socketPtr)
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Close("Close"),
  m_Button_Send("Send data"),
  m_CheckButton_Editable("Editable"),
  m_CheckButton_Visible("Visible"),
  socket(socketPtr)
{
  set_size_request(500, 250);
  set_title("Amateur Radio Remote Controller Client");

  add(m_VBox);

  m_Entry.set_max_length(50);
  m_Entry.set_text("hello");
  m_Entry.set_text(m_Entry.get_text() + " world");
  m_Entry.select_region(0, m_Entry.get_text_length());
  m_VBox.pack_start(m_Entry);

  // Note that add() can also be used instead of pack_xxx()
  m_VBox.add(m_HBox);

  m_HBox.pack_start(m_CheckButton_Editable);
  m_CheckButton_Editable.signal_toggled().connect( sigc::mem_fun(*this,
              &Window::on_checkbox_editable_toggled) );
  m_CheckButton_Editable.set_active(true);

  m_HBox.pack_start(m_CheckButton_Visible);
  m_CheckButton_Visible.signal_toggled().connect( sigc::mem_fun(*this,
              &Window::on_checkbox_visibility_toggled) );
  m_CheckButton_Visible.set_active(true);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &Window::on_button_close) );
  m_Button_Send.signal_clicked().connect( sigc::mem_fun(*this,
          &Window::on_send_clicked) );
  m_VBox.pack_start(m_Button_Send);
  m_Button_Send.set_can_default();
  m_Button_Send.grab_default();

  m_VBox.pack_start(m_Button_Close);
  m_Button_Close.set_can_default();
  m_Button_Close.grab_default();

  show_all_children();
}

Window::~Window()
{
}

void Window::on_checkbox_editable_toggled()
{
  m_Entry.set_editable(m_CheckButton_Editable.get_active());
}

void Window::on_checkbox_visibility_toggled()
{
  m_Entry.set_visibility(m_CheckButton_Visible.get_active());
}

void Window::on_button_close()
{
  hide();
}

void Window::on_send_clicked()
{
	sprintf(socket->msg.data, "%s", m_Entry.get_text().c_str());
	socket->msg.type = 1;
	socket->send(socket->msg);
	unsigned short size;
	socket->recv(socket->msg,size);
	m_Entry.set_text(socket->msg.data);
}
