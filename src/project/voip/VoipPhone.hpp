#ifndef VOIPPHONE_H
#define VOIPPHONE_H
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
#endif //VOIPPHONE_H
