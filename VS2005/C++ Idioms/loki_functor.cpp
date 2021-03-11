#include <iostream>
using namespace std ;
//loki库中的仿函数原理
//注意模板参数可以是void类型

/*
//问题一：已知函数Fun有2个参数，请完成CTestFunctor类，使得CTestFunctor的()实际调用Fun

class CTestCommand
{
public:
	void operator()(int x,double y)
	{
		cout << "CTestCommand的operator" << x << " " << y << endl;
	}
};

void Fun(double x,int y)
{
	cout << "全局函数" << x << " " << y << endl;
}

////////
答案
template<typename FNU,typename R,typename P1,typename P2>
class CTestFunctor
{
public:
	CTestFunctor(const FNU& fun):m_fun(fun)
	{

	};
	R operator()(P1 p1,P2 p2)
	{
		return m_fun(p1,p2);
	}
protected:
	FNU m_fun;
};
/////////

void main()
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void,int,double> f(cmd);
	f(3,4.5);


	CTestFunctor<void (*)(double,int),void,int,double> f2(Fun);
	f2(100,1000);
}
*/

/*
//问题二，参数类型不定，但不超过5个
class CTestCommand
{
public:
	void operator()()
	{
		cout << "无参数" << endl ;
	}
	void operator()(int x )
	{
		cout << "1参数" << endl ;
	}
	int operator()(double x,int y)
	{
		cout << "2参数" << x << " " << y << endl;
		return 2;
	}
	void operator()(char x,char y ,char z )
	{
		cout << "3参数" << x <<" " << y << " " << z << endl ;
	}
	void operator()(short x,short y,short z,short w)
	{
		cout << "4参数" << x <<" " << y << " " << z << " " << w << endl ;
	}
	void operator()(short x,short y,short z,short w,short v)
	{
		cout << "5参数" << x <<" " << y << " " << z << " " << w << " " << v << endl ;
	}
};

class NullType
{
	NullType();//构造函数只有声明，没实现，所以不会被调用
};

template<typename FNU,typename R,typename P1=NullType,typename P2=NullType,typename P3=NullType,typename P4=NullType,typename P5=NullType>
class CTestFunctor
{
public:
	CTestFunctor(const FNU& fun):m_fun(fun)
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

void main()
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void> f0(cmd);
	f0();

	CTestFunctor<CTestCommand,void,int> f1(cmd);
	f1(1);

	CTestFunctor<CTestCommand,int,double,int> f2(cmd);
	int x = f2(1,2);

	CTestFunctor<CTestCommand,void,char,char,char> f3(cmd);
	f3(1,2,3);

	CTestFunctor<CTestCommand,void,short,short,short,short> f4(cmd);
	f4(1,2,3,4);

	CTestFunctor<CTestCommand,void,short,short,short,short,short> f5(cmd);
	f5(1,2,3,4,5);
}
*/
/*
//问题三：假定有默认值。
//CTestCommand改成如下：
class CTestCommand
{
public: 
	void operator()(short x=1,short y=2,short z=3,short w=4,short v=5)
	{
		cout << "5参数" << x <<" " << y << " " << z << " " << w << " " << v << endl ;
	}
};

class NullType
{
	NullType();//构造函数只有声明，没实现，所以不会被调用
};

template<typename FNU,typename R,typename P1=NullType,typename P2=NullType,typename P3=NullType,typename P4=NullType,typename P5=NullType>
class CTestFunctor
{
public:
	CTestFunctor(const FNU& fun):m_fun(fun)
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

//f2改成如下：
void main( )
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void,double,int> f2(cmd);
	//运行正常。
	f2(999,888);
}
*/
/*
//问题四：
//看看容错性如何？

class CTestCommand
{
public: 
	void operator()(short x,short y)
	{
		cout << "5参数" << x <<" " << y  << endl ;
	}
};
假定少一个参数，我们看会报错吧。
void main()
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void,short> f1(cmd);
	f1(1); 
}
报错。
void main()
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void,short,short> f1(cmd);
	f1(1); 
}
报错
void main()
{
	CTestCommand cmd ;
	CTestFunctor<CTestCommand,void,short> f1(cmd);
	f1(1,2); 
}
报错。
编译器，就可以发现参数不一致的错误。
--------------------- 
作者：软件架构师何志丹 
来源：CSDN 
原文：https://blog.csdn.net/he_zhidan/article/details/43150735?utm_source=copy 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

