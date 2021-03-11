/*
#include <iostream>
#include <vector>

template<typename T1, typename T2> // 通例，返回 false
class theSameType       { public: enum { ret = false }; };
template<typename T>               // 特例，两类型相同时返回 true
class theSameType<T, T> { public: enum { ret = true }; };

int main()
{
	std::cout << theSameType< std::vector<int>::iterator::iterator_category,
		std::random_access_iterator_tag >::ret << '\n';
	std::cin.get(); return 0;
}
*/

#include <iostream> // std::cout

// whether T could be converted to U
template<class T, class U>
class ConversionTo
{
	typedef char Type1[1]; // 两种 sizeof 不同的类型
	typedef char Type2[2];
	static Type1& Test( U ); // 较下面的函数，因为参数取值范围小，优先匹配
	static Type2& Test(...); // 变长参数函数，可以匹配任何数量任何类型参数
	static T MakeT(); // 返回类型 T，用这个函数而不用 T() 因为 T 可能没有默认构造函数
public:
	//sizeof对函数的返回值求大小，不会真正调用函数
	//如果 T 可以转换成 U, 那么 Test(MakeT()) 会匹配  Type1& Test( U ); 这个重载, 否则的话会匹配 Type2& Test(...); 然后对应的返回值类型不同, sizeof 结果就不相同, ret 就会得到不同的值
	enum { ret = sizeof(Test(MakeT()))==sizeof(Type1) }; // 可以转换时调用返回 Type1 的 Test()
};

int main10()
{
	std::cout << ConversionTo<int, double>::ret << '\n';
	std::cout << ConversionTo<float, int*>::ret << '\n';
	std::cout << ConversionTo<const int&, int&>::ret << '\n';
	std::cin.get(); return 0;
}