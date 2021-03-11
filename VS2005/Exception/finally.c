#include <windows.h>
#include <stdio.h>

/*
void main()
{
	puts("hello");
	__try
	{
		puts("__try块中");

		// 注意，下面return语句直接让函数返回了
		return;
	}
	__finally
	{
		puts("__finally块中");
	}

	puts("world");
}
*/
/*
void main()
{
	puts("hello");
	__try
	{
		puts("__try块中");

		// 跳转指令
		goto RETURN;
	}
	__finally
	{
		puts("__finally块中");
	}

RETURN:
	puts("world");
}
*/
/*
static void test()
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
	__finally
	{
		// 这里会被执行吗
		puts("__finally块中");
	}

	puts("world");
}

void main()
{
	__try
	{
		test();
	}
	__except(1)
	{
		puts("__except块中");
	}
}
*/
/*
static void test()
{
	puts("hello");
	__try
	{
		int* p;
		puts("__try块中");

		// 直接跳出当前的__try作用域
		__leave;
		p = 0;
		*p = 25;
	}
	__finally
	{
		// 这里会被执行吗？当然
		puts("__finally块中");
	}

	puts("world");
}

void main()
{
	__try
	{
		test();
	}
	__except(1)
	{
		puts("__except块中");
	}
}
*/
static void test1()
{
	char* p1, *p2, *p3, *p4;

	__try
	{
		p1 = malloc(10);
		p2 = malloc(10);
		p3 = malloc(10);
		p4 = malloc(10);

		// do other job
		// 期间可能抛出异常
	}
	__finally
	{
		// 这里保证所有资源被及时释放
		if(p1) free(p1);
		if(p2) free(p2);
		if(p3) free(p3);
		if(p4) free(p4);
	}
}

static void test()
{
	char* p;

	__try
	{
		p = malloc(10);

		// do other job
		// 期间可能抛出异常

		test1();

		// do other job
	}
	__finally
	{
		// 这里保证资源被释放
		if(p) free(p);
	}
}

void main9( void )
{
	__try
	{
		char* p;

		__try
		{
			p = malloc(10);

			// do other job

			// 期间可能抛出异常
			test();

			// do other job
		}
		__finally
		{
			// 这里保证资源被释放
			if(p) free(p);
		}
	}
	__except(1)
	{
		printf("捕获到一个异常/n");
	}
}