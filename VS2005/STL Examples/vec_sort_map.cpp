#include <iostream>
#include <vector>
#include <set>
#include <hash_set>
#include <algorithm>
using namespace std;

int main_sort_map(int argc, char **argv)
{
	size_t arry_i[] = { 9, 2, 3, 7, 5, 1, 4, 6, 8 };
	vector<size_t> vec_i( arry_i, arry_i + 9 );
	
	copy( vec_i.begin(), vec_i.end(), ostream_iterator<size_t>( cout, " " ) );
	cout << endl << "******" << endl;

	set<size_t> set_i( vec_i.begin(), vec_i.end() );
	copy( set_i.begin(), set_i.end(), ostream_iterator<size_t>( cout, " " ) );
	cout << endl << "******" << endl;
	
	return 0;
}
