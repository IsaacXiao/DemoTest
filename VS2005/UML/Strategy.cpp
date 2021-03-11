#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp> 

using namespace std;

struct Discount
{
	virtual void Price( ) = 0;
};

struct discA: public Discount
{
	virtual void Price( ) 
	{ 
		cout << "策略A（0.8折）" << endl;
	}
};

struct discB: public Discount
{
	virtual void Price( ) 
	{ 
		cout << "策略B（消费满200，返券100）" << endl;
	}
};

class Store
{
private:
	Discount * m_pDisc;
public:
	Store( Discount * pDisc ):m_pDisc( pDisc ){ }
	void Sale( )
	{
		m_pDisc->Price( );
	}
};

int main7(int argc, char **argv)
{
	discA da;
	discB db;
	Store store( &da );
	store.Sale( );
	store = Store( &db );
	store.Sale( );

	return 0;
}

