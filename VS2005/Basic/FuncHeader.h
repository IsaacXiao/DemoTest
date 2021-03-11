#pragma once

#include <Windows.h>
#include <iostream>
#include <process.h>
#include <excpt.h>
using namespace std;


typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStack, pfnStartAddr, \
	pvParam, fdwCreate, pdwThreadID)                 \
	((HANDLE) _beginthreadex(                     \
	(void *) (psa),                            \
	(unsigned) (cbStack),                      \
	(PTHREAD_START) (pfnStartAddr),            \
	(void *) (pvParam),                        \
	(unsigned) (fdwCreate),                    \
	(unsigned *) (pdwThreadID))) 


LONG WINAPI FilterFunc( DWORD dwExceptionCode, struct _EXCEPTION_POINTERS *ep )
{
	return ( ( dwExceptionCode == STATUS_STACK_OVERFLOW ) 
		? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH );
}

VOID SomeFunc(PVOID pvDataBuffer)
{ 
	// The first byte in the buffer is some byte of information
	char c = * (PBYTE) pvDataBuffer;       

	_try
	{
		// Increment past the first byte in the buffer 
		pvDataBuffer = (PVOID)((PBYTE) pvDataBuffer + 1); 

		// Bytes 2-5 contain a double-word value
		DWORD dw = * (DWORD *) pvDataBuffer; 
		cout << dw << endl;

		// The line above raises a data misalignment exception on the Alpha
	}
	_except( FilterFunc( GetExceptionCode( ), GetExceptionInformation( ) ) )
	{
		puts("in except");
	}
}

