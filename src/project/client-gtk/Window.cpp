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
m_MainTable(2,2,true),
m_SoundTable(2,2,true),
m_GPIOTable(3,9,true),
m_GPIO2Button("2"),
m_GPIO3Button("3"),
m_GPIO4Button("4"),
m_GPIO7Button("7"),
m_GPIO8Button("8"),
m_GPIO9Button("9"),
m_GPIO10Button("10"),
m_GPIO11Button("11"),
m_GPIO14Button("14"),
m_GPIO15Button("15"),
m_GPIO17Button("17"),
m_GPIO18Button("18"),
m_GPIO22Button("22"),
m_GPIO23Button("23"),
m_GPIO24Button("24"),
m_GPIO25Button("25"),
m_GPIO27Button("27"),
m_PushToTalkButton("Push To Talk"),
socket(socketPtr)
{
  set_size_request(50, 20);
  set_title("Amateur Radio Remote Controller Client");

  //Signals attach
  m_GPIO2Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO2) );
  m_GPIO3Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO3) );
  m_GPIO4Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO4) );
  m_GPIO7Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO7) );
  m_GPIO8Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO8) );
  m_GPIO9Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO9) );
  m_GPIO10Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO10) );
  m_GPIO11Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO11) );
  m_GPIO14Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO14) );
  m_GPIO15Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO15) );
  m_GPIO17Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO17) );
  m_GPIO18Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO18) );
  m_GPIO22Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO22) );
  m_GPIO23Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO23) );
  m_GPIO24Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO24) );
  m_GPIO25Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO25) );
  m_GPIO27Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onClick_GPIO27) );

  m_PushToTalkButton.signal_pressed().connect(sigc::mem_fun(*this, &Window::onPress_PTT) );
  m_PushToTalkButton.signal_released().connect(sigc::mem_fun(*this, &Window::onRelease_PTT) );

  add(m_MainTable);

  m_GPIOFrame.set_label("GPIO Pins");

  m_GPIOFrame.set_border_width(5);
  m_GPIOFrame.add(m_GPIOTable);
  m_GPIOTable.set_homogeneous(true);

  m_MainTable.attach(m_GPIOFrame,0,1,0,1);

  m_GPIOTable.attach(m_GPIO2Button,0,1,0,1);
  m_GPIOTable.attach(m_GPIO3Button,1,2,0,1);
  m_GPIOTable.attach(m_GPIO4Button,2,3,0,1);
  m_GPIOTable.attach(m_GPIO7Button,3,4,0,1);
  m_GPIOTable.attach(m_GPIO8Button,4,5,0,1);
  m_GPIOTable.attach(m_GPIO9Button,5,6,0,1);
  m_GPIOTable.attach(m_GPIO10Button,6,7,0,1);
  m_GPIOTable.attach(m_GPIO11Button,7,8,0,1);
  m_GPIOTable.attach(m_GPIO14Button,8,9,0,1);

  m_GPIOTable.attach(m_GPIO15Button,0,1,1,2);
  m_GPIOTable.attach(m_GPIO17Button,1,2,1,2);
  m_GPIOTable.attach(m_GPIO18Button,2,3,1,2);
  m_GPIOTable.attach(m_GPIO22Button,3,4,1,2);
  m_GPIOTable.attach(m_GPIO23Button,4,5,1,2);
  m_GPIOTable.attach(m_GPIO24Button,5,6,1,2);
  m_GPIOTable.attach(m_GPIO25Button,6,7,1,2);
  m_GPIOTable.attach(m_GPIO27Button,7,8,1,2);

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
  LogAppend(m_refTextBuffer1,(char*)"Connect your Radio software to ./vcom1 serial port");

  m_SoundFrame.set_border_width(5);
  m_SoundFrame.set_label("Sound controls");
  m_MainTable.attach( m_SoundFrame,1,2,0,1);
  m_SoundFrame.add(m_SoundTable);
  m_SoundLatencyLabel.set_label("Audio Latency:");
  m_SoundJittterLabel.set_label("Audio Jitter:");
  m_SoundVolumeLabel.set_label("Audio Volume");
  m_PushToTalkButton.set_label("Push To Talk");
  m_SoundLatencyValueLabel.set_label("0 ms");
  m_SoundJittterValueLabel.set_label("0 ms");
  m_SoundVolumeValueLabel.set_label("100%");
  m_SoundTable.attach(m_SoundLatencyLabel,0,1,0,1);
  m_SoundTable.attach(m_SoundLatencyValueLabel,1,2,0,1);
  m_SoundTable.attach(m_SoundJittterLabel,0,1,1,2);
  m_SoundTable.attach(m_SoundJittterValueLabel,1,2,1,2);
  m_SoundTable.attach(m_SoundVolumeLabel,0,1,2,3);
  m_SoundTable.attach(m_SoundVolumeValueLabel,1,2,2,3);
  m_SoundTable.attach(m_PushToTalkButton,0,2,3,5);
  show_all_children();
  initGPIO();
}

Window::~Window()
{
}

bool Window::isPinOn(unsigned short pin)
{
		socket->msg.type = Msg::GPIO_GET;
		sprintf(socket->msg.data,"%02d",pin);
		socket->send();
		socket->recv();
		char buffer[1] = {socket->msg.data[3]};
		unsigned short value = atoi(buffer);
		printf("Message: %s\nPin %02d has value %d\n",socket->msg.data,pin, value);
		return value;
}

void Window::setPinStatus(unsigned short pin, bool value)
{
	socket->msg.type = Msg::GPIO_SET;
	sprintf(socket->msg.data,"%02d %d",pin, value?1:0);
	socket->send();
	socket->recv();
	char buffer[1] = {socket->msg.data[3]};
	unsigned short returnvalue = atoi(buffer);
	printf("Message: %s\nPin %02d has value %d\n",socket->msg.data,pin, returnvalue);
}


void Window::initGPIO()
{
	m_GPIO2Button.set_active(isPinOn(2));
	m_GPIO3Button.set_active(isPinOn(3));
	m_GPIO4Button.set_active(isPinOn(4));
	m_GPIO7Button.set_active(isPinOn(7));
	m_GPIO8Button.set_active(isPinOn(8));
	m_GPIO9Button.set_active(isPinOn(9));
	m_GPIO10Button.set_active(isPinOn(10));
	m_GPIO11Button.set_active(isPinOn(11));
	m_GPIO14Button.set_active(isPinOn(14));
	m_GPIO15Button.set_active(isPinOn(15));
	m_GPIO17Button.set_active(isPinOn(17));
	m_GPIO18Button.set_active(isPinOn(18));
	m_GPIO22Button.set_active(isPinOn(22));
	m_GPIO23Button.set_active(isPinOn(23));
	m_GPIO24Button.set_active(isPinOn(24));
	m_GPIO25Button.set_active(isPinOn(25));
	m_GPIO27Button.set_active(isPinOn(27));

}

void Window::processGPIOClick(Gtk::ToggleButton *buttonptr, unsigned int pin)
{
	if(buttonptr->get_active()) setPinStatus(pin,true);
	else setPinStatus(pin,false);
	buttonptr->set_active(isPinOn(pin));
}

void Window::onClick_GPIO2(void)
{
	processGPIOClick(&m_GPIO2Button,2);
}

void Window::onClick_GPIO3(void)
{
	processGPIOClick(&m_GPIO3Button,3);
}
void Window::onClick_GPIO4(void)
{
	processGPIOClick(&m_GPIO4Button,4);
}
void Window::onClick_GPIO7(void)
{
	processGPIOClick(&m_GPIO7Button,7);
}
void Window::onClick_GPIO8(void)
{
	processGPIOClick(&m_GPIO8Button,8);
}
void Window::onClick_GPIO9(void)
{
	processGPIOClick(&m_GPIO9Button,9);
}
void Window::onClick_GPIO10(void)
{
	processGPIOClick(&m_GPIO10Button,10);
}
void Window::onClick_GPIO11(void)
{
	processGPIOClick(&m_GPIO11Button,11);
}
void Window::onClick_GPIO14(void)
{
	processGPIOClick(&m_GPIO14Button,14);
}
void Window::onClick_GPIO15(void)
{
	processGPIOClick(&m_GPIO15Button,15);
}
void Window::onClick_GPIO17(void)
{
	processGPIOClick(&m_GPIO17Button,17);
}
void Window::onClick_GPIO18(void)
{
	processGPIOClick(&m_GPIO18Button,18);
}
void Window::onClick_GPIO22(void)
{
	processGPIOClick(&m_GPIO22Button,22);
}
void Window::onClick_GPIO23(void)
{
	processGPIOClick(&m_GPIO23Button,23);
}
void Window::onClick_GPIO24(void)
{
	processGPIOClick(&m_GPIO24Button,24);
}
void Window::onClick_GPIO25(void)
{
	processGPIOClick(&m_GPIO25Button,25);
}
void Window::onClick_GPIO27(void)
{
	processGPIOClick(&m_GPIO27Button,27);
}

void Window::onPress_PTT(void)
{
	setPinStatus(2,true);
	m_GPIO2Button.set_active(isPinOn(2));
}

void Window::onRelease_PTT(void)
{
	setPinStatus(2,false);
	m_GPIO2Button.set_active(isPinOn(2));
}

void Window::setVoipLatencyLabel(const char *label)
{
	this->m_SoundLatencyValueLabel.set_label(label);
}

