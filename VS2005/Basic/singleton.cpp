#include <Windows.h>
#include <iostream>

using namespace std;

void singleInst( )
{
	HANDLE h = CreateMutex(NULL, FALSE, 
		"{FA531CC1-0497-11d3-A180-00105A276C3E}");
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		cout << "There is already an instance of this application running." << endl;
		//return(0);
	}

	cout << "This is the first instance of this application running." << endl;
	while( true );

	// Before exiting, close the object.
	CloseHandle(h);
}