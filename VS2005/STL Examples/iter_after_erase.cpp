#include  <iostream>
#include  <vector>
#include <assert.h>
using namespace std;

//https://blog.csdn.net/skyroben/article/details/70877008

void Printvector( vector<int> &l )
{
	vector<int>::iterator it = l.begin();
	while (it != l.end())
	{
		if (*it % 2 == 0)
		{
			vector<int>::iterator it_test = l.erase(it);    //(1)   1  输出之后崩溃
			assert( it_test == it );
			//it=l.erase(it); //(2)   1 3 5 输出之后崩溃
		}
		if ( it != l.end() )
		{
			cout << *it++ << " ";
		}
//		++it;
	}
	cout << endl;
}
void Testvector()
{
	vector<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	Printvector(l);
}

int main_iter_after_erase()
{
	Testvector();
	return 0;
}