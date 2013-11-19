#ifndef MSGTYPES_H_
#define MSGTYPES_H_

namespace Msg
{
	enum MsgTypes
	{
		UNKNOWN,		//not sure for what, just in case
		FREQUENCY,		//to set rig frequency
		RS232C,			//to be solved later (maybe not needed)
		NOP,			//to say that side is nothing to say
		OTHER_DATA,
		PUSHTOTALK_ON,	//button in microphone pushed
		PUSHTOTALK_OFF, //button in microphone released
		GPIO_ON,		//button in turn on gpio pin
		GPIO_OFF,		//button in turn of gpio pin
	};
};


#endif /* MSGTYPES_H_ */
