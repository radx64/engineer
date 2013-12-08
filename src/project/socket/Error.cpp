/*
 * ===========================================
 * File:   Error.cpp
 * Author: Radoslaw Pawel Szewczyk
 *         184792
 *         Politechnika Wroclawska 2013
 * ===========================================
 */
#include "Error.hpp"

void error(const char* errorMessage)
{
	perror(errorMessage);
}
