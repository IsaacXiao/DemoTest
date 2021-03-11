// alg_remove_copy.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
	using namespace std;
	vector <int> v1, v2(10);
	vector <int>::iterator Iter1, Iter2, new_end;

	int i;
	for ( i = 0 ; i <= 9 ; i++ )
		v1.push_back( i );

	int ii;
	for ( ii = 0 ; ii <= 3 ; ii++ )
		v1.push_back( 7 );

	random_shuffle (v1.begin( ), v1.end( ) );
	cout << "The original vector v1 is:     ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// Remove elements with a value of 7
	new_end = remove_copy ( v1.begin( ), v1.end( ), v2.begin( ), 7 );

	cout << "Vector v1 is left unchanged as ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	cout << "Vector v2 is a copy of v1 with the value 7 removed:\n ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")." << endl;
}