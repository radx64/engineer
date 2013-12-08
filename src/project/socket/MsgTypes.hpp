/*
 * ===========================================
 * File:   MsgTypes.hpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */
#ifndef MSGTYPES_HPP_
#define MSGTYPES_HPP_

namespace Msg
{
	enum MsgTypes
	{
		UNKNOWN,
		NOP,
		OTHER_DATA,
		PUSHTOTALK_ON,
		PUSHTOTALK_OFF,
		GPIO_GET,
		GPIO_SET,
		SERIAL_DATA,
		CONFIG_DATA
	};
};


#endif /* MSGTYPES_HPP_ */
