#include <iostream>
using namespace std;

#include <loki/Functor.h>
using namespace Loki;

#include <vector>

bool calc(int a,int b)
{
	return a > b;
}

template<typename T>
void print(T b, T e, char c=' ')
{
	while(b!=e)
		cout << *b++ << c;
	cout << endl;
}

int main( )
{
	Functor<bool, LOKI_TYPELIST_2(int,int)> lf(calc);

	vector<int> lv;
	for ( int i = 0; i < 10; i++ ) 
	{
		lv.push_back(i);
	}

	print( lv.begin(), lv.end() );
	sort(lv.begin(), lv.end(), lf );
	print( lv.begin(), lv.end() );

	return 0;
}
