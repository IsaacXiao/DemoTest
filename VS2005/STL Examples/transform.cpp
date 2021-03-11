// alg_transform.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

// The function object multiplies an element by a Factor
template <class Type>
class MultValue
{
private:
	Type Factor;   // The value to multiply by
public:
	// Constructor initializes the value to multiply by
	MultValue ( const Type& _Val ) : Factor ( _Val ) {
	}

	// The function call for the element to be multiplied
	int operator ( ) ( Type& elem ) const 
	{
		return elem * Factor;
	}
};

int main_alg_transform( )
{
	using namespace std;
	vector <int> v1, v2 ( 7 ), v3 ( 7 );
	vector <int>::iterator Iter1, Iter2 , Iter3;

	// Constructing vector v1
	int i;
	for ( i = -4 ; i <= 2 ; i++ )
	{
		v1.push_back(  i );
	}

	cout << "Original vector  v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// Modifying the vector v1 in place
	transform (v1.begin ( ) , v1.end ( ) , v1.begin ( ) , MultValue<int> ( 2 ) );
	cout << "The elements of the vector v1 multiplied by 2 in place gives:"
		<< "\n v1mod = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// Using transform to multiply each element by a factor of 5
	transform ( v1.begin ( ) , v1.end ( ) , v2.begin ( ) , MultValue<int> ( 5 ) );

	cout << "Multiplying the elements of the vector v1mod\n "
		<<  "by the factor 5 & copying to v2 gives:\n v2 = ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")." << endl;

	// The second version of transform used to multiply the 
	// elements of the vectors v1mod & v2 pairwise
	transform ( v1.begin ( ) , v1.end ( ) ,  v2.begin ( ) , v3.begin ( ) , 
		multiplies <int> ( ) );

	cout << "Multiplying elements of the vectors v1mod and v2 pairwise "
		<<  "gives:\n v3 = ( " ;
	for ( Iter3 = v3.begin( ) ; Iter3 != v3.end( ) ; Iter3++ )
		cout << *Iter3 << " ";
	cout << ")." << endl;

	return 0;
}