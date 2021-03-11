#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

//模板元的另一个应用场景：编译（而非运行）时断言
template<bool> struct StaticAssert;	//通用情形下只声明不定义
template<> struct StaticAssert<true>{ };	//特化情形下的定义
#define STATIC_ASSERT( e )	StaticAssert<(e)>()

int main4(int argc, char **argv)
{
	const int i = 4; //如果是 i = 3 则下面这句会在编译时报错
	STATIC_ASSERT( i % 2 == 0 );

	return 0;
}
