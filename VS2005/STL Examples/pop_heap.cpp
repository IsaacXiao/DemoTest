// alg_pop_heap.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

int main_pop_heap( )  
{
	using namespace std;
	
	int arry_int[ ] = { 65, 50, 68, 19, 31, 32, 26, 21, 16, 13, 24 };

	vector <int> v1( arry_int, arry_int + 11 );

	//random_shuffle( v1.begin( ), v1.end( ) );
	copy( v1.begin(), v1.end(), ostream_iterator<int>( cout, " ") );
	cout << endl;

	make_heap( v1.begin(), v1.end() );
	copy( v1.begin(), v1.end(), ostream_iterator<int>( cout, " ") );
	cout << endl;

	pop_heap( v1.begin( ), v1.end( ) );
	copy( v1.begin(), v1.end(), ostream_iterator<int>( cout, " ") );
	cout << endl;

	return 0;
}