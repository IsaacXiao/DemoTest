#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

//specialization and partial specialization
template<typename To, typename From>
struct CastAndPrint
{
	CastAndPrint( From f ) { cout << ( To )f << endl; }
};

template<>
struct CastAndPrint<int, const char*>
{
	CastAndPrint( const char* s ) { cout << ( int )atoi( s ) << endl; }
};

template<typename To>
struct CastAndPrint<To, const char*>
{
	CastAndPrint( const char* s ) { cout << ( To )atoi( s ) << endl; }
};

int main2(int argc, char **argv)
{
	CastAndPrint<int, float>( 3.1415f );
	CastAndPrint<int, const char*>( "67" );
	CastAndPrint<char, const char*>( "67" );

	return 0;
}
