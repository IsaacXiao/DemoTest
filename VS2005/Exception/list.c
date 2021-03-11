#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _EXCEPTION_REGISTRATION
{
	struct _EXCEPTION_REGISTRATION *prev;
	DWORD handler;
}EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;


// 异常监控函数
EXCEPTION_DISPOSITION myHandler
(
	EXCEPTION_RECORD *ExcRecord,
	void * EstablisherFrame,
	CONTEXT *ContextRecord,
	void * DispatcherContext
)
{
	printf("进入到异常处理模块中/n");
	printf("不进一步处理异常，程序直接终止退出/n");

	abort();
	return ExceptionContinueExecution;
}


int main3()
{
	DWORD prev;
	EXCEPTION_REGISTRATION reg, *preg;

	// 建立异常结构帧（EXCEPTION_REGISTRATION）
	reg.handler = (DWORD)myHandler;

	// 把异常结构帧插入到链表中
	__asm
	{
		mov eax, fs:[0]
		mov prev, eax
	}
	//fs:[0]为指向SEH链指针，把它赋值给reg的prev
	//此行代码为把系统默认的异常处理函数作为reg的外层处理函数
	reg.prev = (EXCEPTION_REGISTRATION*) prev;

	// 注册监控函数
	//把reg的回调函数注册为这个程序的默认异常处理函数
	preg = &reg;
	__asm
	{
		mov eax, preg
		mov fs:[0], eax
	}

	{
		int* p;
		p = 0;

		// 下面的语句被执行，将导致一个异常
		*p = 45;
	}

	printf("这里将不会被执行到./n");

	return 0;
}