#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

//此例演示为何模板元编程能提高运行时效率
template<int I> 
struct Fac 
{ 
	static const int Value = I * Fac<I-1>::Value;
};

template<>
struct Fac<1>
{
	static const int Value = 1;
};

template<int I> struct Evaluator;

int main3(int argc, char **argv)
{
	//cout << Fac<5>::Value << endl;
	//下面这行代码，（很多）编译器会报错：Evaluator<120> 类没有构造函数，可见120是在编译时计算的
	//Evaluator<Fac<5>::Value>( ); 

	//应用场景：编译（而非运行）时求值
	//#define EVAL(t) Evaluator<t::Value>( )
	//EVAL( Fac<5> );

	return 0;
}
