/*
 * Window.cpp
 *
 *  Created on: 11 lis 2013
 *      Author: radek
 */

#include "Window.h"

 void LogAppend(Glib::RefPtr<Gtk::TextBuffer> buffer, char *text)
 {
	 char time_buf[20];
	 time_t rawtime;
	 struct tm * timeinfo;
	 time (&rawtime);
	 timeinfo = localtime (&rawtime);
	 strftime (time_buf,80,"[%Y-%m-%d %H:%M:%S]\t",timeinfo);
	 buffer->set_text(buffer->get_text() +time_buf + text + "\n");
 }

Glib::ustring createFrequencyMarkup(unsigned int frequency)
{
	Glib::ustring ret;
	Glib::ustring milions   = Glib::ustring::format(std::setfill(L'0'), std::setw(3),frequency/1000000);
	Glib::ustring thousands = Glib::ustring::format(std::setfill(L'0'), std::setw(3),(frequency % 1000000) / 1000);
	Glib::ustring  ones     = Glib::ustring::format(std::setfill(L'0'), std::setw(3),frequency%1000);
	ret = Glib::ustring::compose("%1 %2.%3.%4 %5", "<span font_family=\"monospace\" size=\"28000\" background=\"#00CC00\">",milions,thousands,ones,"Hz </span>");
	return ret;
}


Window::Window(TcpSocket *socketPtr)
:
freq(0),
m_MainTable(2,2,true),
m_FrequencyTable(7,9,true),
m_FrequencyAdd1Button("+1"),
m_FrequencyAdd10Button("+10"),
m_FrequencyAdd100Button("+100"),
m_FrequencyAdd1kButton("+1k"),
m_FrequencyAdd10kButton("+10k"),
m_FrequencyAdd100kButton("+100k"),
m_FrequencyAdd1MButton("+1M"),
m_FrequencyAdd10MButton("+10M"),
m_FrequencyAdd100MButton("+100M"),
m_FrequencyRemove1Button("-1"),
m_FrequencyRemove10Button("-10"),
m_FrequencyRemove100Button("-100"),
m_FrequencyRemove1kButton("-1k"),
m_FrequencyRemove10kButton("-10k"),
m_FrequencyRemove100kButton("-100k"),
m_FrequencyRemove1MButton("-1M"),
m_FrequencyRemove10MButton("-10M"),
m_FrequencyRemove100MButton("-100M"),
m_FrequencyManualEntryButton("Manual"),
m_FrequencySetButton("Set frequency"),
m_ModulationAMButton("AM"),
m_ModulationCWButton("CW"),
m_ModulationUSBButton("USB"),
m_ModulationLSBButton("LSB"),
m_ModulationRTTYButton("RTTY"),
m_ModulationFMNarrowButton("FM\nNarrow"),
m_ModulationFMWideButton("FM\nWide"),
m_ModulationCWRevButton("CW\nRev"),
m_ModulationRTTYRevButton("RTTY\nRev"),
socket(socketPtr)
{
  set_size_request(50, 20);
  set_title("Amateur Radio Remote Controller Client");

  //Signals attach
  m_FrequencyAdd1Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq1) );
  m_FrequencyAdd10Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq10) );
  m_FrequencyAdd100Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq100) );
  m_FrequencyAdd1kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq1k) );
  m_FrequencyAdd10kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq10k) );
  m_FrequencyAdd100kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq100k) );
  m_FrequencyAdd1MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq1M) );
  m_FrequencyAdd10MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq10M) );
  m_FrequencyAdd100MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::incFreq100M) );
  m_FrequencyRemove1Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq1) );
  m_FrequencyRemove10Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq10) );
  m_FrequencyRemove100Button.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq100) );
  m_FrequencyRemove1kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq1k) );
  m_FrequencyRemove10kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq10k) );
  m_FrequencyRemove100kButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq100k) );
  m_FrequencyRemove1MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq1M) );
  m_FrequencyRemove10MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq10M) );
  m_FrequencyRemove100MButton.signal_clicked().connect( sigc::mem_fun(*this, &Window::decFreq100M) );

  add(m_MainTable);

  m_FrequencyFrame.set_label("Radio frequency:");
  m_FrequencyFrame.set_border_width(5);
  m_FrequencyFrame.add(m_FrequencyTable);
  m_FrequencyTable.set_homogeneous(true);

  m_MainTable.attach(m_FrequencyFrame,0,1,0,1);

  m_FrequencyTable.attach(m_FrequencyEntryLabel,1,7,1,2);
  m_FrequencyEntryLabel.set_markup(createFrequencyMarkup(freq));

  m_FrequencyTable.attach(m_FrequencyManualEntryButton,7,9,1,2);
  m_FrequencyTable.attach(m_FrequencyAdd100MButton,0,1,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd10MButton,1,2,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd1MButton,2,3,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd100kButton,3,4,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd10kButton,4,5,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd1kButton,5,6,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd100Button,6,7,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd10Button,7,8,0,1);
  m_FrequencyTable.attach(m_FrequencyAdd1Button,8,9,0,1);

  m_FrequencyTable.attach(m_FrequencyRemove100MButton,0,1,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove10MButton,1,2,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove1MButton,2,3,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove100kButton,3,4,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove10kButton,4,5,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove1kButton,5,6,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove100Button,6,7,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove10Button,7,8,2,3);
  m_FrequencyTable.attach(m_FrequencyRemove1Button,8,9,2,3);


  m_FrequencyTable.attach(m_FrequencySetButton,0,9,3,4);

  m_ModulationLabel.set_text("Mode:");

  m_FrequencyTable.attach(m_ModulationLabel,0,9,5,6);
  m_FrequencyTable.attach(m_ModulationAMButton,0,1,6,7);
  m_FrequencyTable.attach(m_ModulationCWButton,1,2,6,7);
  m_FrequencyTable.attach(m_ModulationCWRevButton,2,3,6,7);
  m_FrequencyTable.attach(m_ModulationUSBButton,3,4,6,7);
  m_FrequencyTable.attach(m_ModulationLSBButton,4,5,6,7);
  m_FrequencyTable.attach(m_ModulationRTTYButton,5,6,6,7);
  m_FrequencyTable.attach(m_ModulationRTTYRevButton,6,7,6,7);
  m_FrequencyTable.attach(m_ModulationFMNarrowButton,7,8,6,7);
  m_FrequencyTable.attach(m_ModulationFMWideButton,8,9,6,7);
  m_FrequencyTable.set_spacings(1);


  m_LogFrame.set_label("Log:");
  m_LogFrame.set_border_width(5);
  m_MainTable.attach(m_LogFrame,0,2,1,2);
  m_ScrolledWindow.add(m_LogView);
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindow.set_border_width(5);
  m_refTextBuffer1 = Gtk::TextBuffer::create();
  m_LogView.set_buffer(m_refTextBuffer1);
  m_LogFrame.add(m_ScrolledWindow);
  LogAppend(m_refTextBuffer1,(char*)"Welcome in ARRCC");

  m_SoundFrame.set_border_width(5);
  m_SoundFrame.set_label("Sound controls");
  m_MainTable.attach( m_SoundFrame,1,2,0,1);






  show_all_children();
}

Window::~Window()
{
}

void Window::updateFrequencyDelta(signed int deltaFrequency)
{
	if(((deltaFrequency < 0) && ((signed int)Window::freq+deltaFrequency >=0)) || ((deltaFrequency > 0) && ((signed int)Window::freq+deltaFrequency <=999999999)))
	{
		Window::freq+=deltaFrequency;
		Window::m_FrequencyEntryLabel.set_markup(createFrequencyMarkup(Window::freq));
	}
}

void Window::updateFrequency(unsigned int Frequency)
{
	Window::freq=Frequency;
	Window::m_FrequencyEntryLabel.set_markup(createFrequencyMarkup(Window::freq));
}

void Window::incFreq1()
{
	updateFrequencyDelta(1);
}
void Window::incFreq10()
{
	updateFrequencyDelta(10);
}
void Window::incFreq100()
{
	updateFrequencyDelta(100);
}
void Window::incFreq1k()
{
	updateFrequencyDelta(1000);
}
void Window::incFreq10k()
{
	updateFrequencyDelta(10000);
}
void Window::incFreq100k()
{
	updateFrequencyDelta(100000);
}
void Window::incFreq1M()
{
	updateFrequencyDelta(1000000);
}
void Window::incFreq10M()
{
	updateFrequencyDelta(10000000);
}
void Window::incFreq100M()
{
	updateFrequencyDelta(100000000);
}
void Window::decFreq1()
{
	updateFrequencyDelta(-1);
}
void Window::decFreq10()
{
	updateFrequencyDelta(-10);
}
void Window::decFreq100()
{
	updateFrequencyDelta(-100);
}
void Window::decFreq1k()
{
	updateFrequencyDelta(-1000);
}
void Window::decFreq10k()
{
	updateFrequencyDelta(-10000);
}
void Window::decFreq100k()
{
	updateFrequencyDelta(-100000);
}
void Window::decFreq1M()
{
	updateFrequencyDelta(-1000000);
}
void Window::decFreq10M()
{
	updateFrequencyDelta(-10000000);
}
void Window::decFreq100M()
{
	updateFrequencyDelta(-100000000);
}
