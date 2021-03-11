// map_key_comp.cpp
// compile with: /EHsc
#include <map>
#include <iostream>

int main_map_comp( )
{
	using namespace std;

	map <int, int, less<int> > m1;
	map <int, int, less<int> >::key_compare kc1 = m1.key_comp( ) ;
	bool result1 = kc1( 2, 3 ) ;
	if( result1 == true )
	{
		cout << "kc1( 2,3 ) returns value of true, "
			<< "where kc1 is the function object of m1."
			<< endl;
	}
	else   
	{
		cout << "kc1( 2,3 ) returns value of false "
			<< "where kc1 is the function object of m1."
			<< endl;
	}

	map <int, int, greater<int> > m2;
	map <int, int, greater<int> >::key_compare kc2 = m2.key_comp( );
	bool result2 = kc2( 2, 3 ) ;
	if( result2 == true )
	{
		cout << "kc2( 2,3 ) returns value of true, "
			<< "where kc2 is the function object of m2."
			<< endl;
	}
	else   
	{
		cout << "kc2( 2,3 ) returns value of false, "
			<< "where kc2 is the function object of m2."
			<< endl;
	}

	return 0;
}
/*
// map_value_comp.cpp
// compile with: /EHsc
#include <map>
#include <iostream>

int main( )
{
	using namespace std;

	map <int, int, less<int>> m1;
	map <int, int, less<int>>::value_compare vc1 = m1.value_comp( );
	pair<map<int,int>::iterator, bool> pr1, pr2;

	pr1= m1.insert ( map <int, int> :: value_type ( 1, 10 ) );
	pr2= m1.insert ( map <int, int> :: value_type ( 2, 5 ) );

	if( vc1( *pr1.first, *pr2.first ) == true )   
	{
		cout << "The element ( 1,10 ) precedes the element ( 2,5 )."
			<< endl;
	}
	else   
	{
		cout << "The element ( 1,10 ) does not precede the element ( 2,5 )."
			<< endl;
	}

	if(vc1( *pr2.first, *pr1.first ) == true )
	{
		cout << "The element ( 2,5 ) precedes the element ( 1,10 )."
			<< endl;
	}
	else   
	{
		cout << "The element ( 2,5 ) does not precede the element ( 1,10 )."
			<< endl;
	}
}
*/
