#include "Error.hpp"

void error(const char* errorMessage)
{
	perror(errorMessage);
	exit(1);
}
