#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;


// 实现的条件 if 语句
// 通例为空，若不匹配特例将报错，很好的调试手段（这里是 bool 就无所谓了）
template<bool c, typename Then, typename Else>
class IF_ { };

template<typename Then, typename Else>
class IF_<true, Then, Else>
{ 
	public: typedef Then reType;
};

template<typename Then, typename Else>
class IF_<false,Then, Else>
{ 
	public: 
		typedef Else reType;
};

int main5(int argc, char **argv)
{
	const int len = 8;
	//注意模板实例化是由外到内的，这很关键
	//根据每个等号==表达式为true还是false来决定使用哪个特化版本的IF_
	//编译器的实例化先从最外层的尖括号<>开始，依次递归往内进行
	//如果没有一个数据类型的长度等于len，则编译器会报错
	typedef
		IF_<sizeof(short)==len, short,
		IF_<sizeof(int)==len, int,
		IF_<sizeof(long)==len, long,
		IF_<sizeof(long long)==len, long long,
		void>::reType>::reType>::reType>::reType
		int_my; // 定义一个指定字节数的类型
	std::cout << sizeof(int_my) << '\n';

	return 0;
}
