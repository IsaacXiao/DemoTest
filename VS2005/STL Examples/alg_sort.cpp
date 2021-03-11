// alg_sort.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <functional>      // For greater<int>( )
#include <iostream>

// Return whether first element is greater than the second
bool UDgreater ( int elem1, int elem2 )
{
	return elem1 > elem2;
}

int main_alg_sort( )
{
	using namespace std;
	vector <int> v1;
	vector <int>::iterator Iter1;

	int i;
	for ( i = 0 ; i <= 5 ; i++ )
	{
		v1.push_back( 2 * i );
	}

	int ii;
	for ( ii = 0 ; ii <= 5 ; ii++ )
	{
		v1.push_back( 2 * ii + 1 );
	}

	cout << "Original vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	sort( v1.begin( ), v1.end( ) );
	cout << "Sorted vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	// To sort in descending order. specify binary predicate
	sort( v1.begin( ), v1.end( ), greater<int>( ) );
	cout << "Resorted (greater) vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	// A user-defined (UD) binary predicate can also be used
	sort( v1.begin( ), v1.end( ), UDgreater );
	cout << "Resorted (UDgreater) vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	return 0;
}