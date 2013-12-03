#include "Error.hpp"

void error(const char* errorMessage)
{
	perror(errorMessage);
}
