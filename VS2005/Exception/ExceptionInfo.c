#include <windows.h>
#include <stdio.h>

int exception_access_violation_filter(LPEXCEPTION_POINTERS p_exinfo)
{
	if(p_exinfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		printf("存储保护异常/n");
		return 1;
	}
	else return 0;
}

int exception_int_divide_by_zero_filter(LPEXCEPTION_POINTERS p_exinfo)
{
	if(p_exinfo->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
	{
		printf("被0除异常/n");
		return 1;
	}
	else return 0;
}

void main7()
{
	puts("hello");
	__try
	{
		__try
		{
			int* p;

			// 下面将导致一个异常
			p = 0;
			*p = 45;
		}
		// 注意，__except模块捕获一个存储保护异常
		__except(exception_access_violation_filter(GetExceptionInformation()))
		{
			puts("内层的except块中");
		}
	}
	// 注意，__except模块捕获一个被0除异常
	__except(exception_int_divide_by_zero_filter(GetExceptionInformation()))
	{
		puts("外层的except块中");
	}

	puts("world");
}