/*
 * ===========================================
 * File:   VoipPhone.hpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */
#ifndef VOIPPHONE_HPP_
#define VOIPPHONE_HPP_
#include <linphone/linphonecore.h>

class VoipPhone
{
private:
    LinphoneCoreVTable vtable;
    LinphoneCore *lc;
    LinphoneCall *call;

public:
	VoipPhone(int port);
	~VoipPhone();
	const char* getVersion();
	static void callStateChanged(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
	void setPort(int port);
	int getPort(void);
	void loop(void);
	void terminate(void);
	void makeCall(char *destination);

};
#endif //VOIPPHONE_HPP_
