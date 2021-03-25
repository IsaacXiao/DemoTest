#include <windows.h>

SYSTEMTIME SetSec(SYSTEMTIME d) 
{
	if (d.wSecond == 0) 
	{
		d.wSecond=59;
		if(d.wMinute == 0) 
		{
			d.wMinute=59;
			if(d.wHour == 0)
				d.wHour=23;
				else 
					d.wHour--;
		} 
			else 
				d.wMinute--;
	} 
	else 
		d.wSecond--;
	return d;
}