/*
 * ===========================================
 * File:   GPIO.hpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

class GPIO
{
public:
	GPIO();
	GPIO(string gnum);
	~GPIO();
    int setdir_gpio(string dir);
    int setval_gpio(string val);
    int getval_gpio(string& val);
    string get_gpionum();
private:
    int export_gpio();
	int unexport_gpio();
	
	int valuefd;
	int directionfd;
	int exportfd;
	int unexportfd;
	string gpionum;
	
};

#endif /* GPIO_HPP_ */
