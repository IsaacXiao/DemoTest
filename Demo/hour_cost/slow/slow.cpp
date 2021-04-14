#include "../platform/IncludeHeader.h"
#include <stdlib.h>

void os_sleep(size_t Milliseconds)
{
	return Sleep(Milliseconds);
}


void SlowFunc() 
{
	while (rand() % 2) 
	{
		os_sleep(34);
	}
}


