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
	void incFreq1();
	void incFreq10();
	void incFreq100();
	void incFreq1k();
	void incFreq10k();
	void incFreq100k();
	void incFreq1M();
	void incFreq10M();
	void incFreq100M();


	void decFreq1();
	void decFreq10();
	void decFreq100();
	void decFreq1k();
	void decFreq10k();
	void decFreq100k();
	void decFreq1M();
	void decFreq10M();
	void decFreq100M();

	//End of signal handlers

	void updateFrequencyDelta(signed int deltaFrequency);
	void updateFrequency(unsigned int Frequency);
	unsigned int freq; //temporary freq for gui testing




	//Child widgets:
	//Main table for positioning all elements
	Gtk::Table m_MainTable;
	//End of main table

	//Frequency frame
	Gtk::Frame m_FrequencyFrame;
	Gtk::Table m_FrequencyTable;
	Gtk::Label m_FrequencyEntryLabel;
	Gtk::Button m_FrequencyManualEntryButton;
	Gtk::Button m_FrequencyAdd1Button;
	Gtk::Button m_FrequencyAdd10Button;
	Gtk::Button m_FrequencyAdd100Button;
	Gtk::Button m_FrequencyAdd1kButton;
	Gtk::Button m_FrequencyAdd10kButton;
	Gtk::Button m_FrequencyAdd100kButton;
	Gtk::Button m_FrequencyAdd1MButton;
	Gtk::Button m_FrequencyAdd10MButton;
	Gtk::Button m_FrequencyAdd100MButton;

	Gtk::Button m_FrequencyRemove1Button;
	Gtk::Button m_FrequencyRemove10Button;
	Gtk::Button m_FrequencyRemove100Button;
	Gtk::Button m_FrequencyRemove1kButton;
	Gtk::Button m_FrequencyRemove10kButton;
	Gtk::Button m_FrequencyRemove100kButton;
	Gtk::Button m_FrequencyRemove1MButton;
	Gtk::Button m_FrequencyRemove10MButton;
	Gtk::Button m_FrequencyRemove100MButton;

	Gtk::Label m_ModulationLabel;
	Gtk::ToggleButton m_ModulationAMButton;
	Gtk::ToggleButton m_ModulationCWButton;
	Gtk::ToggleButton m_ModulationUSBButton;
	Gtk::ToggleButton m_ModulationLSBButton;
	Gtk::ToggleButton m_ModulationRTTYButton;
	Gtk::ToggleButton m_ModulationFMNarrowButton;
	Gtk::ToggleButton m_ModulationFMWideButton;
	Gtk::ToggleButton m_ModulationCWRevButton;
	Gtk::ToggleButton m_ModulationRTTYRevButton;

	Gtk::Button m_FrequencySetButton;
	//End of frequency frame

	//Log frame
	Gtk::Frame m_LogFrame;
	Gtk::ScrolledWindow m_ScrolledWindow;
	Gtk::TextView m_LogView;
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1;
	//End of log frame

	//VOIP frame
	Gtk::Frame m_SoundFrame;

	//End of VOIP frame
	TcpSocket *socket;

};

#endif /* GTKMM_WINDOW_H_ */





