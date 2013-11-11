/*
linphone
Copyright (C) 2010  Belledonne Communications SARL 
 (simon.morlat@linphone.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifdef IN_LINPHONE
#include "linphonecore.h"
#else
#include "linphone/linphonecore.h"
#endif

#include <signal.h>

static bool_t running=TRUE;

static void stop(int signum){
        running=FALSE;
}

/*
 * Call state notification callback
 */
static void call_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg){
	LinphoneChatRoom* chat_room = linphone_core_create_chat_room(lc,"sip:radek@192.168.1.100:9998");
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
                		linphone_chat_room_send_message(chat_room,"Welcome in room!\n");
                		linphone_core_accept_call(lc,call);


                break;
                case LinphoneCallIncomingEarlyMedia:
                		printf("Call incoming....!");

                break;
                default:
                        printf("Unhandled notification %i\n",cstate);
        }
}
/*
static void text_received(LinphoneCore *lc, LinphoneChatRoom *room, const LinphoneAddress *from, const char *message)
{
	printf("Got message from %s in room %s: %s\n", linphone_address_get_username(from), linphone_address_get_domain(from) ,message);
	linphone_chat_room_send_message(room,"Hi! I'm server!\n");
}
*/

int main(int argc, char *argv[]){
        LinphoneCoreVTable vtable={0};
        LinphoneCore *lc;
        LinphoneCall *call=NULL;

        signal(SIGINT,stop);

        printf("Version: %s\n",linphone_core_get_version());

#ifdef DEBUG
        linphone_core_enable_logs(NULL); /*enable liblinphone logs.*/
#endif
        /* 
         Fill the LinphoneCoreVTable with application callbacks.
         All are optional. Here we only use the call_state_changed callbacksestablished
         in order to get notifications about the progress of the call.
         */
        vtable.call_state_changed=call_state_changed;
        vtable.text_received=text_received;

        /*
         Instanciate a LinphoneCore object given the LinphoneCoreVTable
        */
        //linphone_core_disable_logs();
        lc=linphone_core_new(&vtable,NULL,NULL,NULL);
        linphone_core_set_sip_port(lc, 9999);

        linphone_core_iterate(lc);

        //LinphoneChatRoom* chat_room = linphone_core_create_chat_room(lc,"sip:radek@192.168.1.100:9998");
        //linphone_chat_room_send_message(chat_room,"Welcome in room!\n");

        /* main loop for receiving notifications and doing background linphonecore work: */
        while(running){
                linphone_core_iterate(lc);
                ms_usleep(50000);
        }
        if (call && linphone_call_get_state(call)!=LinphoneCallEnd){
                /* terminate the call */
                printf("Terminating the call...\n");
                linphone_core_terminate_call(lc,call);
                /*at this stage we don't need the call object */
                linphone_call_unref(call);
        }

end:
        printf("Shutting down...\n");
        linphone_core_destroy(lc);
        printf("Exited\n");
        return 0;
}
