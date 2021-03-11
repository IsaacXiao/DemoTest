
#include <string>
using namespace std;

class MyCmd
{
public:
	virtual ~MyCmd(){ }
	//实际用的是它
	virtual void operator()( const string & msg )
	{
		
	}
	//其余的全部注释掉
	/*virtual void operator()()
	{

	}
	virtual void operator()(int x )
	{

	}
	virtual int operator()(double x,int y)
	{
		
	}
	virtual void operator()(char x,char y ,char z )
	{
		
	}
	virtual void operator()(short x,short y,short z,short w)
	{
		
	}
	virtual void operator()(short x,short y,short z,short w,short v)
	{
		
	}*/
};

class NullType
{
	NullType();//构造函数只有声明，没实现，所以不会被调用
};

template<typename FNU,typename R,typename P1=NullType,typename P2=NullType,typename P3=NullType,typename P4=NullType,typename P5=NullType>
class MyFunctor
{
public:
	MyFunctor(const FNU& fun):m_fun(fun)
	{

	};
	R operator()()
	{
		return m_fun();
	};
	R operator()(P1 p1)
	{
		return m_fun(p1);
	};
	R operator()(P1 p1,P2 p2)
	{
		return m_fun(p1,p2);
	};
	R operator()(P1 p1,P2 p2,P3 p3)
	{
		return m_fun(p1,p2,p3);
	};
	R operator()(P1 p1,P2 p2,P3 p3,P4 p4)
	{
		return m_fun(p1,p2,p3,p4);
	};
	R operator()(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
	{
		return m_fun(p1,p2,p3,p4,p5);
	};
protected:
	FNU m_fun;
};
