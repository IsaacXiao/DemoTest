#include <stdio.h>
#include <Windows.h>

/*
int seh_filer()
{
	return 0;
}

static void test()
{
	__try
	{
		int* p;

		puts("test()函数的try块中");

		// 下面将导致一个异常
		p = 0;
		*p = 45;
	}
	// 注意，__except关键字后面的表达式是一个函数表达式
	// 而且这个函数将返回0，所以控制流进入到上一层
	// 的try-except语句中继续查找
	__except(seh_filer())
	{
		puts("test()函数的except块中");
	}
}

void main()
{
	puts("hello");
	__try
	{
		puts("main()函数的try块中");

		// 注意，这个函数的调用过程中，有可能出现一些异常
		test();
	}
	// 注意，这个表达式是一个逗号表达式
	// 它前部分打印出一条message，后部分是
	// 一个常量，所以这个值也即为整个表达式
	// 的值，因此系统找到了__except定义的异
	// 常处理模块，控制流进入到__except模块里面
	__except(puts("in filter"), 1)
	{
		puts("main()函数的except块中");
	}

	puts("world");
}
*/

int ExceptFilter( struct _EXCEPTION_POINTERS * ep )
{
	ep->ContextRecord->Ecx = 1;
	return EXCEPTION_CONTINUE_EXECUTION;
}

void main5()
{
	int j;
	volatile int zero;

	puts("hello");
	__try
	{
		puts("main()函数的try块中");

		zero = 0;
		j = 10;
		// 下面将导致一个异常
		j = 45 / zero;

		// 注意，异常出现后，程序控制流又恢复到了这里
		printf("这里会执行到吗？值有如何呢？j=%d /n", j);
	}
	// 注意，这里把zero变量赋值为1，试图恢复错误，
	// 当控制流恢复到原来异常点时，避免了异常的再次发生
	//__except( (puts("in filter"), zero = 1), -1 )
	__except( ExceptFilter( GetExceptionInformation( ) ) )
	{
		puts("main()函数的except块中");
	}

	puts("world");
}
