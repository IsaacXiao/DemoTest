#include <iostream>
#include "my_functor.h"

#include <list>


template<typename SigSubT, typename SlotObsT>
class QObject
{
	MyCmd cmd;
	//CTestFunctor<CTestCommand,void> f0(cmd);
	//f0();
	MyFunctor<MyCmd, void, const string &> my_signal;
	MyFunctor<MyCmd, void, const string &> my_slot;
public:
	virtual ~QObject( ){ }
	//未完成，有空用loki或者boost中的functor来玩
	static void connect( const SigSubT * subject, MyFunctor<MyCmd, void, const string &> SIGNAL , const SlotObsT * observer, MyFunctor<MyCmd, void, const string &> SLOT )
	{
		//注册发送者的notify函数与接收者的update函数
		subject.Attach( observer );
		my_signal = SIGNAL;
		my_slot = SLOT;
		
		//TODO
		//1. 子类的信号与槽都是成员函数，需在这个connect里绑定
		//2. 建立m_signal_fun与Notify的连接
		//3. 建立m_slot_fun与Update的连接
	}

	//实际上lstObs与Attach该保存signal函数
	//在Notify的时候查找该函数并调用它
	void Notify( )
	{
		for ( list<const SlotObsT*>::iterator it = lstObs.begin(); it != lstObs.end(); ++ it )
		{
			it->Update( );
		}
	}

	virtual void Attach( const SlotObsT * observer )
	{
		lstObs.push_back( observer );
	}
	virtual void Detach( const SlotObsT * observer )
	{
		lstObs.remove( observer );
	}
protected:
	list<const SlotObsT*> lstObs;
};

//前置声明
class Reader;

//Subject类
class Newspaper : public QObject<Newspaper, Reader>
{
public:
	//该函数即为Notify
	void send( const string & msg ) const
	{
		//调用QObject的Notify
	}
private:
	string m_name;
};

//Observer类
class Reader :  public QObject<Newspaper, Reader>
{
public:
	void Update( )
	{
		//调用receiveNewspaper
	}
	//该函数即为Update
	void receiveNewspaper( const string & msg ) const
	{
		cout << "Receives Newspaper: " << endl;
	}
};

int main_bak(int argc, char **argv)
{
	

	return 0;
}

