// iterator_advance.cpp
// compile with: /EHsc
#include <iterator>
#include <list>
#include <iostream>

int main_iterator_advance( )
{
	using namespace std;
	int i;

	list<int> L;
	for ( i = 1 ; i < 9 ; ++i )  
	{
		L.push_back ( i );
	}
	list <int>::iterator L_Iter, LPOS = L.begin ( );

	cout << "The list L is: ( ";
	for ( L_Iter = L.begin( ) ; L_Iter != L.end( ); L_Iter++)
		cout << *L_Iter << " ";
	cout << ")." << endl;

	cout << "The iterator LPOS initially points to the first element: "
		<< *LPOS << "." << endl;

	advance ( LPOS , 4 );
	cout << "LPOS is advanced 4 steps forward to point"
		<< " to the fifth element: "
		<< *LPOS << "." << endl;

	advance ( LPOS , -3 );
	cout << "LPOS is moved 3 steps back to point to the "
		<< "2nd element: " << *LPOS << "." << endl;

	return 0;
}