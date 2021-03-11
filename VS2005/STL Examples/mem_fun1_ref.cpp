#include <functional>
#include <stdio.h>

struct A
{
	A(int n):n_(n)
	{
	 }

	 int add(int n)
	 {
		return n+n_;
	}

	 int test()
	 {
		return n_;
	}

	int n_;
};

void main_mem_fun1_ref()
{
	A a(10);
	int n = std::mem_fun_ref(&A::test)(a);
	int n2 = std::mem_fun1_ref(&A::add)(a,100);

	printf("%d\n", n);    //10
	printf("%d\n", n2);    //110
}