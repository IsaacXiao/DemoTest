/*
#include <stdio.h>
void main()
{
	puts("hello");

	__try
	{
		int* p;
		puts("__try块中");

		// 下面抛出一个异常
		p = 0;
		*p = 25;
	}
	__except(1)
	{
		puts("__except块中");
	}

	__try
	{
	}
	__finally
	{
		puts("__finally块中");
	}

	puts("world");
}
*/
/*
#include <stdio.h>

void main()
{
	puts("hello");

	__try
	{
		__try
		{
			int* p;
			puts("__try块中");

			// 下面抛出一个异常
			p = 0;
			*p = 25;
		}
		__finally
		{
			// 这里会被执行吗
			puts("__finally块中");
		}
	}
	__except(1)
	{
		puts("__except块中");
	}

	puts("world");
}
*/

/*
// 例程3，try-finally语句中嵌套try-except
#include <stdio.h>

void main()
{
	puts("hello");

	__try
	{
		__try
		{
			int* p;
			puts("__try块中");

			// 下面抛出一个异常
			p = 0;
			*p = 25;
		}
		__except(1)
		{
			puts("__except块中");
		}
	}
	__finally
	{
		puts("__finally块中");
	}

	puts("world");
}
*/

#include <stdio.h>

static void test()
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
			puts("这里不会被执行到");
		}
		__finally
		{
			//注意打印顺序运行结果，这行在两个filter展开后
			puts("in finally");
		}

		// 呵呵，注意这条语句
		puts("这里也不会被执行到");
	}
	//括号内的条件表达式为0，异常会交由上一级处理
	__except(puts("in filter 1"), 0)
	{
		puts("in except 1");
	}
}

void main10()
{
	puts("hello");
	__try
	{
		test();
	}
	//括号内的条件表达式为1，异常在本级处理
	__except(puts("in filter 2"), 1)
	{
		puts("in except 2");
	}
	puts("world");
}



