#include <gtkmm-3.0/gtkmm.h>
#include "../socket/TcpSocket.hpp"
#include "../voip/VoipPhone.hpp"
#include <time.h>
#include <iomanip>

#ifndef GTKMM_WINDOW_H_
#define GTKMM_WINDOW_H_

class Window : public Gtk::Window
{
public:
	Window(TcpSocket *socketPtr);
	virtual ~Window();


protected:
	//Signal handlers:
	void onClick_GPIO2(void);
	void onClick_GPIO3(void);
	void onClick_GPIO4(void);
	void onClick_GPIO7(void);
	void onClick_GPIO8(void);
	void onClick_GPIO9(void);
	void onClick_GPIO10(void);
	void onClick_GPIO11(void);
	void onClick_GPIO14(void);
	void onClick_GPIO15(void);
	void onClick_GPIO17(void);
	void onClick_GPIO18(void);
	void onClick_GPIO22(void);
	void onClick_GPIO23(void);
	void onClick_GPIO24(void);
	void onClick_GPIO25(void);
	void onClick_GPIO27(void);
	//End of signal handlers

	//Child widgets:
	//Main table for positioning all elements
	Gtk::Table m_MainTable;
	//End of main table

	//Frequency frame
	Gtk::Frame m_GPIOFrame;
	Gtk::Table m_GPIOTable;
	Gtk::ToggleButton m_GPIO2Button; //used to pushtotalk
	Gtk::ToggleButton m_GPIO3Button;
	Gtk::ToggleButton m_GPIO4Button;
	Gtk::ToggleButton m_GPIO7Button;
	Gtk::ToggleButton m_GPIO8Button;
	Gtk::ToggleButton m_GPIO9Button;
	Gtk::ToggleButton m_GPIO10Button;
	Gtk::ToggleButton m_GPIO11Button;
	Gtk::ToggleButton m_GPIO14Button;
	Gtk::ToggleButton m_GPIO15Button;
	Gtk::ToggleButton m_GPIO17Button;
	Gtk::ToggleButton m_GPIO18Button;
	Gtk::ToggleButton m_GPIO22Button;
	Gtk::ToggleButton m_GPIO23Button;
	Gtk::ToggleButton m_GPIO24Button;
	Gtk::ToggleButton m_GPIO25Button;
	Gtk::ToggleButton m_GPIO27Button;

	//End of frequency frame

	//Log frame
	Gtk::Frame m_LogFrame;
	Gtk::ScrolledWindow m_ScrolledWindow;
	Gtk::TextView m_LogView;
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1;
	//End of log frame

	//VOIP frame
	Gtk::Frame m_SoundFrame;
	Gtk::Table m_SoundTable;
	Gtk::Label m_SoundLatencyLabel;
	Gtk::Label m_SoundJittterLabel;
	Gtk::Label m_SoundVolumeLabel;
	Gtk::Label m_SoundLatencyValueLabel;
	Gtk::Label m_SoundJittterValueLabel;
	Gtk::Label m_SoundVolumeValueLabel;
	Gtk::Button m_PushToTalkButton;
	//End of VOIP frame
	TcpSocket *socket;

};

#endif /* GTKMM_WINDOW_H_ */





