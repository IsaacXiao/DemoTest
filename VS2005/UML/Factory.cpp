#include <string>
#include <iostream>

using namespace std;

template<typename T>
class COperation
{
public:
	virtual T GetResult( T a, T b ) = 0;
};

template<typename T>
class Add : public COperation<T>
{
public:
	virtual T GetResult( T a, T b )
	{
		return a + b;
	}
};

template<typename T>
class Sub : public COperation<T>
{
public:
	virtual T GetResult( T a, T b )
	{
		return a - b;
	}
};

class CalcFactory
{
public:
	template<typename T>
	COperation<T> * Create( const char szType ) const
	{
		switch( szType )
		{
		case '+':
			return new Add<T>;
		case '-':
			return new Sub<T>;
		default:
			return NULL;
		}
	}
};

int main1(int argc, char **argv)
{
	CalcFactory calc_f;
	COperation<long> * pAdd = calc_f.Create<long>( '+' );
	cout << pAdd->GetResult( 2, 3 ) << endl;
	delete pAdd;

	COperation<long> * pSub = calc_f.Create<long>( '-' );
	cout << pSub->GetResult( 5, 1 ) << endl;
	delete pSub;

	return 0;
}

