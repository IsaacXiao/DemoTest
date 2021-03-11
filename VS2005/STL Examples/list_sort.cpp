// list_sort.cpp
// compile with: /EHsc
#include <list>
#include <iostream>

int main_list_sort( )
{
	using namespace std;
	list <int> c1;
	list <int>::iterator c1_Iter;

	c1.push_back( 20 );
	c1.push_back( 10 );
	c1.push_back( 30 );
	c1.push_back( 90 );
	c1.push_back( 70 );

	cout << "Before sorting: c1 =";
	for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
		cout << " " << *c1_Iter;
	cout << endl;

	c1.sort( );
	cout << "After sorting c1 =";
	for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
		cout << " " << *c1_Iter;
	cout << endl;

	c1.sort( greater<int>( ) );
	cout << "After sorting with 'greater than' operation, c1 =";
	for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
		cout << " " << *c1_Iter;
	cout << endl;

	return 0;
}