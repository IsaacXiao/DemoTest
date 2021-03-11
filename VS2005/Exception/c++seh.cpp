#include "stdio.h" 
/*
class MyException 
{ 
public: 
	MyException() {printf(" 构造一个 MyException 对象 \n");} 
	MyException(const MyException& e) {printf(" 复制一个 MyException 对象 \n");} 
	void operator=(const MyException& e) {printf(" 赋值一个 MyException 对象 \n");} 
	~MyException() {printf(" 析构一个 MyException 对象 \n");} 
}; 
class A 
{ 
public: 
	A() {printf(" 构造一个 A 对象 \n");} 
	~A() {printf(" 析构一个 A 对象 \n");} 
	void f1() {} 
	// 注意，这里抛出了一个 MyException 类型的异常对象 
	void f2() {MyException e; throw e;} 
}; 
// 这个函数中使用了 try-catch 处理异常，也即 C++ 异常处理 
void test1() 
{ 
	A a1; 
	A a2,a3; 
	try 
	{ 
		a2.f1(); 
		a3.f2(); 
	} 
	// 这里虽然有 catch 块，但是它捕获不到上面抛出的 C++ 异常对象 
	catch(int errorcode) 
	{ 
		printf("catch exception,error code:%d\n", errorcode); 
	} 
} 
// 这个函数没什么改变，仍然采用 try-except 异常机制，也即 SEH 机制 
void test() 
{ 
	int* p = 0x00000000; // pointer to NULL 
	__try 
	{ 
		// 这里调用 test1 函数 
		// 注意， test1 函数中会抛出一个 C++ 异常对象 
		test1(); 
		//因为test1内的异常处理不了，所以下面的代码都不会被执行到
		puts("in try"); 
		__try 
		{ 
			puts("in try"); 
			*p = 13; 
			puts(" 这里不会被执行到 "); 
		} 
		__finally //这个__finally是与同级__try嵌套配对的，所以执行不到
		{ 
			puts("in finally"); 
		} 
		puts(" 这里也不会被执行到 "); 
	} 
	__except(puts("in filter 1"), 0) 
	{ 
		puts("in except 1"); 
	} 
} 

void main() 
{ 
	puts("hello"); 
	__try 
	{ 
		test(); 
	} 
	// 这里能捕获到 C++ 异常对象吗？拭目以待吧！ 
	__except(puts("in filter 2"), 1) 
	{ 
		puts("in except 2"); 
	} 
	puts("world"); 
} 
*/
/*
class MyException 
{ 
public: 
	MyException() {printf(" 构造一个 MyException 对象 \n");} 
	MyException(const MyException& e) {printf(" 复制一个 MyException 对象 \n");} 
	void operator=(const MyException& e) {printf(" 复制一个 MyException 对象 \n");} 
	~MyException() {printf(" 析构一个 MyException 对象 \n");} 
}; 
class A 
{ 
public: 
	A() {printf(" 构造一个 A 对象 \n");} 
	~A() {printf(" 析构一个 A 对象 \n");} 
	void f1() {} 
	// 抛出 C++ 异常 
	void f2() {MyException e; throw e;} 
}; 
void test() 
{ 
	int* p = 0x00000000; // pointer to NULL 
	__try 
	{ 
		puts("in try"); 
		__try 
		{ 
			puts("in try"); 
			// causes an access violation exception; 
			// 导致一个存储异常 
			*p = 13; 
			// 呵呵，注意这条语句 
			puts(" 这里不会被执行到 "); 
		} 
		__finally 
		{ 
			puts("in finally"); 
		} 
		// 呵呵，注意这条语句 
		puts(" 这里也不会被执行到 "); 
	} 
	__except(puts("in filter 1"), 0) 
	{ 
		puts("in except 1"); 
	} 
} 
void test1() 
{ 
	A a1; 
	A a2,a3; 
	try 
	{ 
		// 这里会产生一个 SEH 类型的系统异常 
		test(); 
		a2.f1(); 
		a3.f2(); 
	} 
	// 捕获得到吗？ 
	catch(...) 
	{ 
		printf("catch unknown exception\n"); 
	} 
} 
void main() 
{ 
	puts("hello"); 
	__try 
	{ 
		test1(); 
	} 
	__except(puts("in filter 2"), 0) 
	{ 
		puts("in except 2"); 
	} 
	puts("world"); 
} 
*/
/*
//这样写会编译报错
void main() 
{ 
	int* p = 0x00000000; // pointer to NULL 
	// 这里是 SEH 的异常处理语法 
	__try 
	{ 
		puts("in try"); 
		// 这里是 C++ 的异常处理语法 
		try 
		{ 
			puts("in try"); 
			// causes an access violation exception; 
			// 导致一个存储异常 
			*p = 13; 
			// 呵呵，注意这条语句 
			puts(" 这里不会被执行到 "); 
		} 
		catch(...) 
		{ 
			puts("catch anything"); 
		} 
		// 呵呵，注意这条语句 
		puts(" 这里也不会被执行到 "); 
	} 
	__except(puts("in filter 1"), 1) 
	{ 
		puts("in except 1"); 
	} 
} 
*/
/*
//这样写也会编译报错
class A 
{ 
public: 
	A() {printf(" 构造一个 A 对象 /n");} 
	~A() {printf(" 析构一个 A 对象 /n");} 
	void f1() {} 
	void f2() {} 
}; 
void main() 
{ 
	__try 
	{ 
		A a1, a2; 
		puts("in try"); 
	} 
	__except(puts("in filter 1"), 1) 
	{ 
		puts("in except 1"); 
	} 
} 
*/
