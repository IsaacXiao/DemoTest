#include "boost/shared_ptr.hpp"
#include <cassert>

class A {
	boost::shared_ptr<int> no_;
public:
	A(boost::shared_ptr<int> no) : no_(no) {}
	void value(int i) {
		*no_=i;
	}
};

class B {
	boost::shared_ptr<int> no_;
public:
	B(boost::shared_ptr<int> no) : no_(no) {}
	int value() const {
		return *no_;
	}
};
/************************************************************************/
/* 
 类 A和 B都保存了一个 shared_ptr<int>. 在创建 A和 B的实例时，shared_ptr temp被传送到它们的构造函数。这意味着共有三个 shared_ptr：a, b, 和 temp，它们都引向同一个int实例。如果我们用指针来实现对一个的共享，A和 B必须能够在某个时间指出这个int要被删除。在这个例子中，直到main的结束，引用计数为3，当所有 shared_ptr离开了作用域，计数将达到0，而最后一个智能指针将负责删除共享的 int.
*/
/************************************************************************/
int main() 
{
	boost::shared_ptr<int> temp(new int(14));
	A a(temp);
	B b(temp);
	a.value(28);
	/*assert( false );*/
	assert(b.value()==28);
}
