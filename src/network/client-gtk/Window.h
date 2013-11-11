#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"

#ifndef GTKMM_WINDOW_H_
#define GTKMM_WINDOW_H_

class Window : public Gtk::Window
{
public:
	Window(TcpSocket *socketPtr);
	virtual ~Window();

protected:
  //Signal handlers:
  void on_checkbox_editable_toggled();
  void on_checkbox_visibility_toggled();
  void on_button_close();
  void on_send_clicked();

  //Child widgets:
  Gtk::Box m_HBox;
  Gtk::Box m_VBox;
  Gtk::Entry m_Entry;
  Gtk::Button m_Button_Send;
  Gtk::Button m_Button_Close;
  Gtk::CheckButton m_CheckButton_Editable, m_CheckButton_Visible;
  TcpSocket *socket;
};

#endif /* GTKMM_WINDOW_H_ */





