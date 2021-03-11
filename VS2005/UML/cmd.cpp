#include <string>
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace std;

namespace
{
	//命令的执行者：UML上的receiver
	class BarbCuer
	{
	public:
		void BakeMutton() 
		{
			cout << "烤羊肉串" << endl;
		}
		void BakeChickenWing() 
		{
			cout << "烤鸡翅" << endl;
		}
	};
#if 0
	class Cmd
	{
	protected:
		//BarbCuer* cooker;
		//void (BarbCuer::*bake_func_)();
		boost::function<void()> bake_func_;
	public:
		Cmd( /*BarbCuer* c, 
			void(BarbCuer::*bake_func)()*/
			boost::function<void()> bake_func ):
		/*cooker( c ), */
			bake_func_(bake_func){ }
		/*virtual */void BakeSome()  //= 0;
		{
			//(cooker->*bake_func_)();
			if ( bake_func_ )
			{
				bake_func_();
			}	
		}
		virtual ~Cmd(){ }
	};

	class MuttonCmd: public Cmd
	{
	public:
		MuttonCmd(  BarbCuuer* c ):Cmd( c ){ }
		virtual void BakeSome() 
		{
			cooker->BakeMutton();
		}
	};

	class ChickenCmd: public Cmd
	{
	public:
		ChickenCmd(  BarbCuuer* c ):Cmd( c ){ }
		virtual void BakeSome() 
		{
			cooker->BakeChickenWing();
		}
	};
#endif

	typedef boost::function<void()> Cmd2;
	//纯粹用于保存functor为后续调用的
	class Waiter
	{
		//list<Cmd*> order;
		list<Cmd2> order2;
	public:
		//void SetCmd( Cmd * dish )
		//{
		//	order.push_back( dish );
		//}
		//void NotifyExecude()
		//{
		//	for ( list<Cmd*>::iterator it = order.begin(); it != order.end(); ++it )
		//	{
		//		(*it)->BakeSome();
		//	}
		//}

		void SetCmd2( Cmd2 & dish )
		{
			order2.push_back( dish );
		}
		void NotifyExecude2()
		{
			for ( list<Cmd2>::iterator it = order2.begin(); it != order2.end(); ++it )
			{
				(*it)();
			}
		}
	};
}

int main_cmd( )
{
	Waiter w;
	BarbCuer bc;
	//Cmd * Mut1 = new Cmd(&bc, &BarbCuer::BakeMutton);
	//Cmd * Mut2 = new Cmd(&bc, &BarbCuer::BakeMutton);
	//Cmd * ck = new Cmd(&bc, &BarbCuer::BakeChickenWing);

	//Cmd Mut1(boost::bind(&BarbCuer::BakeMutton,&bc));
	//Cmd Mut2(boost::bind(&BarbCuer::BakeMutton,&bc));
	//Cmd ck(boost::bind(&BarbCuer::BakeChickenWing,&bc));
	//w.SetCmd( &Mut1 );
	//w.SetCmd( &Mut2 );
	//w.SetCmd( &ck );
	//w.NotifyExecude();

	Cmd2 Mut1(boost::bind(&BarbCuer::BakeMutton,&bc));
	Cmd2 Mut2(boost::bind(&BarbCuer::BakeMutton,&bc));
	Cmd2 ck(boost::bind(&BarbCuer::BakeChickenWing,&bc));
	w.SetCmd2( Mut1 );
	w.SetCmd2( Mut2 );
	w.SetCmd2( ck );
	w.NotifyExecude2();

	//delete Mut1;
	//delete Mut2;
	//delete ck;

	return 0;
}

