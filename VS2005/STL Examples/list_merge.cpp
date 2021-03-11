// list_merge.cpp
// compile with: /EHsc
#include <list>
#include <iostream>

int main_list_merge( ) 
{
	using namespace std;
	list <int> c1, c2, c3;
	list <int>::iterator c1_Iter, c2_Iter, c3_Iter;

	c1.push_back( 3 );
	c1.push_back( 6 );
	c2.push_back( 2 );
	c2.push_back( 4 );
	c3.push_back( 5 );
	c3.push_back( 1 );

	cout << "c1 =";
	for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
		cout << " " << *c1_Iter;
	cout << endl;

	cout << "c2 =";
	for ( c2_Iter = c2.begin( ); c2_Iter != c2.end( ); c2_Iter++ )
		cout << " " << *c2_Iter;
	cout << endl;

	c2.merge( c1 );  // Merge c1 into c2 in (default) ascending order
	c2.sort( greater<int>( ) );
	cout << "After merging c1 with c2 and sorting with >: c2 =";
	for ( c2_Iter = c2.begin( ); c2_Iter != c2.end( ); c2_Iter++ )
		cout << " " << *c2_Iter;
	cout << endl;

	cout << "c1 =";
	for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
		cout << " " << *c1_Iter;
	cout << endl;

	return 0;
}