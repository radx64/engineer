/*
 * ===========================================
 * File:   VoipPhone.hpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */
#include "VoipPhone.hpp"

VoipPhone::VoipPhone(int port)
{
    call=NULL;
    vtable.call_state_changed= callStateChanged;
    lc=linphone_core_new(&vtable,NULL,NULL,NULL);
    VoipPhone::setPort(port);
}

VoipPhone::~VoipPhone()
{
	linphone_core_destroy(lc);
}

const char* VoipPhone::getVersion()
{
	return 	linphone_core_get_version();
}

void VoipPhone::callStateChanged(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{
    switch(cstate){
            case LinphoneCallOutgoingRinging:
                    printf("It is now ringing remotely !\n");
            break;
            case LinphoneCallOutgoingEarlyMedia:
                    printf("Receiving some early media\n");
            break;
            case LinphoneCallConnected:
                    printf("We are connected !\n");
            break;
            case LinphoneCallStreamsRunning:
                    printf("Media streams established !\n");
            break;
            case LinphoneCallEnd:
                    printf("Call is terminated.\n");
            break;
            case LinphoneCallError:
                    printf("Call failure !");
            break;
            case LinphoneCallIncomingReceived:
            		printf("Call incoming received !: %s\n",msg);
            		linphone_call_ref(call);
            		printf("Remote address: %s\n",linphone_call_get_remote_address_as_string(call));
            		linphone_core_accept_call(lc,call);
            break;
            case LinphoneCallIncomingEarlyMedia:
            		printf("Call incoming....!");

            break;
            default:
                    printf("Unhandled notification %i\n",cstate);
    }
}

void VoipPhone::setPort(int port)
{
    linphone_core_set_sip_port(lc, port);
}

int VoipPhone::getPort(void)
{
    return linphone_core_get_sip_port(lc);
}

void VoipPhone::loop(void)
{
	linphone_core_iterate(lc);
}

void VoipPhone::terminate(void)
{
    linphone_core_terminate_call(lc, call);
    linphone_call_unref(call);
}

void VoipPhone::makeCall(char *destination)
{
	call=linphone_core_invite(lc,destination);
    if (call==NULL)
    {
    	printf("Could not place call to %s\n",destination);
    }
    else  printf("Call to %s is in progress...",destination);
    linphone_call_ref(call);
}
