#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>


jmp_buf mark;

static void test1()
{
	char* p1, *p2, *p3, *p4;
	p1 = malloc(10);
	if (!p1) longjmp(mark, 1);

	p2 = malloc(10);
	if (!p2)
	{
		// 这里虽然可以释放资源，
		// 但是程序员很容易忘记，也容易出错
		free(p1);
		longjmp(mark, 1);
	}

	p3 = malloc(10);
	if (!p3)
	{
		// 这里虽然可以释放资源
		// 但是程序员很容易忘记，也容易出错
		free(p1);
		free(p2);
		longjmp(mark, 1);
	}

	p4 = malloc(10);
	if (!p4)
	{
		// 这里虽然可以释放资源
		// 但是程序员很容易忘记，也容易出错
		free(p1);
		free(p2);
		free(p3);
		longjmp(mark, 1);
	}

	// do other job

	free(p1);
	free(p2);
	free(p3);
	free(p4);
}

void test()
{
	char* p;
	p = malloc(10);

	// do other job

	test1();

	// do other job

	// 这里的资源可能得不到释放
	free(p);
}

void main2( void )
{
	int jmpret;

	jmpret = setjmp( mark );
	if( jmpret == 0 )
	{
		char* p;
		p = malloc(10);

		// do other job

		test1();

		// do other job
		// 这里的资源可能得不到释放
		free(p);
	}
	else
	{
		printf("捕获到一个异常/n");
	}
}