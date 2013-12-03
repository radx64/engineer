#ifndef MSGTYPES_H_
#define MSGTYPES_H_

namespace Msg
{
	enum MsgTypes
	{
		UNKNOWN,		//not sure for what, just in case
		NOP,			//to say that side is nothing to say
		OTHER_DATA,
		PUSHTOTALK_ON,	//button in microphone pushed
		PUSHTOTALK_OFF, //button in microphone released
		GPIO_GET,		//to drive GPIO pins
		GPIO_SET		//same as above
	};
};


#endif /* MSGTYPES_H_ */
