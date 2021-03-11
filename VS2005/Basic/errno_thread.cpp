#include <stdio.h>
#include <errno.h>
#include <io.h>
#include <string.h>
#include <math.h>
#include "FuncHeader.h"

DWORD WINAPI ThreadProc1( LPVOID pParam )
{
	//调用errno之前必须先将其清零
	errno = 0;
	//FILE *fp = fopen("test.txt","r");
	int s = sqrt( (float)-1 );
	int res = errno;
	printf( "errno函数的地址：%p\n", &errno );
	//cout << "errno addr is at: " << &errno << endl;
	printf( "errno = %d\n", res );
	printf("错误信息： %s\n",strerror(errno));

	Sleep( 2000 );

	_endthreadex( 0 );
	return 0;
}
//2个线程里的errno都是jmp同样的地址
//0043BC39  jmp         _errno (44E110h) 
//注意用printf是可重入的
//不会2个线程抢占控制台
//而cout是不可重入的
//会出现2个线程抢占控制台
DWORD WINAPI ThreadProc2( LPVOID pParam )
{
	//调用errno之前必须先将其清零
	errno = 0;
	FILE *fp = fopen("test.txt","r");
	//int s = sqrt( (float)-1 );
	int res = errno;
	printf( "errno函数的地址：%p\n", &errno );
	//cout <<  "errno addr is at: " << &errno << endl;
	printf( "errno = %d\n", res );
	printf("错误信息： %s\n",strerror(errno));

	Sleep( 2000 );

	_endthreadex( 0 );
	return 0;
}

DWORD WINAPI ThreadProc3( LPVOID pParam )
{
	//char szBuf[100];
	//szBuf[10000] = 0; // Stack underflow 
	BYTE aBytes[ 0x10 ];
	MEMORY_BASIC_INFORMATION mbi;
	SIZE_T size = VirtualQuery( aBytes, &mbi, sizeof( mbi ) );

	SIZE_T s = ( SIZE_T )mbi.AllocationBase + 1024*1024;
	PBYTE pAddress = ( PBYTE )s;
	BYTE * pBytes = ( BYTE* )VirtualAlloc( pAddress, 0x10000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );

	aBytes[0x10000] = 1;

	Sleep( 2000 );
	_endthreadex( 0 );
	return 0;
}

void CreateErr( )
{	
	/*HANDLE hThread1 = CreateThread( NULL, 0,
								  ThreadProc1, 0, 0, 0 );

	HANDLE hThread2 = CreateThread( NULL, 0, 
						   ThreadProc2, 0, 0, 0 );
	
	HANDLE  hThread1 = (HANDLE)chBEGINTHREADEX( NULL, 0,
		ThreadProc1, 0, 0, 0 );
	HANDLE  hThread2 = (HANDLE)chBEGINTHREADEX( NULL, 0,
		ThreadProc2, 0, 0, 0 );

	WaitForSingleObject( hThread1, INFINITE );
	WaitForSingleObject( hThread2, INFINITE );

	CloseHandle( hThread1 );
	CloseHandle( hThread2 );*/
	HANDLE  hThread3 = (HANDLE)chBEGINTHREADEX( NULL, 0,
		ThreadProc3, 0, 0, 0 );

	WaitForSingleObject( hThread3, INFINITE );

	CloseHandle( hThread3 );
}

void err_test( )
{
	//调用errno之前必须先将其清零
	errno = 0;
	//FILE *fp = fopen("test.txt","r");
	int s = sqrt( (float)-1 );
	int res = errno;
	printf( "errno = %d\n", res );
	printf("错误信息： %s\n",strerror(errno));
}