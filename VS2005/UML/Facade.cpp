#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp> 

using namespace std;

struct Goods
{
	virtual string name( ) = 0;
};

struct Stocks: public Goods
{
	virtual string name( ) { return "Stocks"; }
};

struct Futures: public Goods
{
	virtual string name( ) { return "Futures"; }
};

struct Bonds: public Goods
{
	virtual string name( ) { return "Bonds"; }
};

class FundAssist
{
public:
	FundAssist( ):m_Stocks( new Stocks ), m_Futures( new Futures ), m_Bonds( new Bonds )
	{
		
	}
	void BuyAggressive( )
	{
		cout << "Buy Aggressive Goods:\t" << m_Stocks->name( ) << "\t" << m_Futures->name( ) << endl;
	}
	void BuySteady( )
	{
		cout << "Buy Steady Goods:\t" << m_Bonds->name( ) << endl;
	}
private:
	boost::shared_ptr<Stocks> m_Stocks;
	boost::shared_ptr<Futures> m_Futures;
	boost::shared_ptr<Bonds> m_Bonds;
};

int main5(int argc, char **argv)
{
	FundAssist fundassist;
	fundassist.BuyAggressive();
	fundassist.BuySteady();

	return 0;
}
