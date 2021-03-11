#include <iostream>
using namespace std;

#include <time.h>

class ProtocolT
{

};

class IDBAction 
{
public:
	virtual void operator()() = 0;
};

class IDBAccess : public ProtocolT
{
public:
	template<typename PtoT, typename TupleT>
	void AddAction()
	{
		class DBQueryAction : public IDBAction
		{		
			virtual void operator()()
			{
				cout << "DBQueryAction::operator()()" << endl;
			}
		};
		cout << "IDBAccess::AddAction" << endl;
	}
};

class RstbPtoProtocol : public IDBAccess
{
public:
	RstbPtoProtocol( ) {
		AddAction<char,int>();
	}	
};

int main( )
{
	/*IDBAction * actions_;
	(*actions_)();*/
	/*RstbPtoProtocol rs;
	rs.AddAction();*/

	return 0;
}

