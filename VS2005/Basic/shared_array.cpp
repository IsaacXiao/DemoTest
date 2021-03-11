#include <iostream>
#include <ios>
#include <boost/smart_ptr.hpp>
using namespace boost;
using namespace std;

int main()
{
	//shared_array<int> sp(new int[100]);	
	//a dynamic array
	int *p = new int[100];
	//shared_array agent dynamic array
	shared_array<int> sa(p);
	//shared array,add reference count
	shared_array<int> sa2 = sa;
	sa[0] = 10;
	if ( sa2[0]==10 )
	{ 
		cout << "TRUE" << endl;
	}
	cout << "use count:" << sa.use_count() << endl;
	cout << "No Problem..." << endl;
	//out of scope,remove dynamic array automatically
	return 0;
}
