#include <setjmp.h>
#include <stdio.h>
#include <process.h>

void main1()
{
	jmp_buf env;
	int i;

	i = setjmp( env );
	printf( "i = %d\n", i );
	if ( i )
	{
		exit( 0 );
	}

	longjmp( env, 2 );
	printf( "This line does not get printed\n" );
}