// set_insert.cpp
// compile with: /EHsc
#include <set>
#include <iostream>

int main_rbtree_set_insert( )
{
	using namespace std;
	set <int>::iterator s1_pIter, s2_pIter;

	set <int, less<int> > s1, s2;
	s1.insert( 10 );
	s1.insert( 7 );
	s1.insert( 8 );

	s1.insert( 15 );

	s1.insert( 5 );
	s1.insert( 6 );

	//s1.insert( 11 );
	s1.insert( 10 );

	s1.insert( 13 );
	s1.insert( 12 );

	cout << "The original s1 =";
	for ( s1_pIter = s1.begin( ); s1_pIter != s1.end( ); s1_pIter++ )
		cout << " " << *s1_pIter;
	cout << "." << endl;

	return 0;
}