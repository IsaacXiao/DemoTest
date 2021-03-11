#include <windows.h>
#include <stdio.h>


typedef struct _EXCEPTION_REGISTRATION
{
	struct _EXCEPTION_REGISTRATION *prev;
	DWORD handler;
}EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;


/************************************************************************/
/* 
栈结构从上到下依次为：
系统默认的异常处理函数
pFunc_exception
SEH链指针指向当前栈的ESP位置
*/
/************************************************************************/
#define SEH_PROLOGUE(pFunc_exception)\
{\
	DWORD pFunc = (DWORD)pFunc_exception;\
	_asm mov eax, FS:[0] \
	_asm push pFunc \
	_asm push eax \
	_asm mov FS:[0], esp \
}\

#define SEH_EPILOGUE() \
{ \
	_asm pop FS:[0] \
	_asm pop eax \
}

void printfErrorMsg(int ex_code)
{
	char msg[20];

	memset(msg, 0, sizeof(msg));
	switch (ex_code)
	{
	case EXCEPTION_ACCESS_VIOLATION :
		strcpy(msg, "存储保护异常");
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED :
		strcpy(msg, "数组越界异常");
		break;
	case EXCEPTION_BREAKPOINT :
		strcpy(msg, "断点异常");
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO :
	case EXCEPTION_INT_DIVIDE_BY_ZERO :
		strcpy(msg, "被0除异常");
		break;
	default :
		strcpy(msg, "其它异常");
	}

	printf("\n");
	printf("%s，错误代码为：0x%x\n", msg, ex_code);
}

EXCEPTION_DISPOSITION my_exception_Handler
(
	EXCEPTION_RECORD *ExcRecord,
	void * EstablisherFrame,
	CONTEXT *ContextRecord,
	void * DispatcherContext
)
{
	int _ebp;

	printfErrorMsg(ExcRecord->ExceptionCode);

	printf("跳过出现异常函数，返回到上层函数中继续执行\n");
	printf("\n");

	_ebp = ContextRecord->Ebp;
	_asm
	{
		// 恢复上一个异常帧
		mov eax, EstablisherFrame
		mov eax, [eax]
		mov fs:[0], eax

		// 返回到上一层的调用函数
		mov esp, _ebp
		pop ebp
		mov eax, -1
		ret
	}

	// 下面将绝对不会被执行到
	exit(0);
	return ExceptionContinueExecution;
}

/************************************************************************/
/* 
第二个参数为PEXCEPTION_REGISTRATION类型，既当前的异常帧指针。第三个参数为指向CONTEXT数据结构的指针，CONTEXT数据结构体中记录了异常发生时，线程当时的上下文环境，主要包括寄存器的值，这一点有点类似于setjmp函数的作用。第四个参数DispatcherContext，它也是一个指针，表示调度的上下文环境，这个参数一般不被用到。                */
/************************************************************************/
EXCEPTION_DISPOSITION my_RaiseException_Handler(
	EXCEPTION_RECORD *ExcRecord,
	void * EstablisherFrame,
	CONTEXT *ContextRecord,
	void * DispatcherContext)
{
	int _ebp;

	printfErrorMsg(ExcRecord->ExceptionCode);

	printf("跳过出现异常函数，返回到上层函数中继续执行\n");
	printf("\n");

	_ebp = ContextRecord->Ebp;
	_asm
	{
		// 恢复上一个异常帧
		mov eax, EstablisherFrame
		mov eax, [eax]
		mov fs:[0], eax

		// 返回到上一层的调用函数
		//跳出当前函数
		mov esp, _ebp
		pop ebp
		//跳出当前函数的上一级函数
		mov esp, ebp
		pop ebp
		mov eax, -1
		ret
	}

	// 下面将绝对不会被执行到
	exit(0);
	return ExceptionContinueExecution;
}


static void test1()
{
	SEH_PROLOGUE(my_exception_Handler);

	{
		int zero;
		int j;
		zero = 0;

		// 下面的语句被执行，将导致一个异常
		j = 10 / zero;

		printf("在test1()函数中，这里将不会被执行到.j=%d\n", j);
	}

	SEH_EPILOGUE();
}

void test2()
{
	SEH_PROLOGUE(my_exception_Handler);

	{
		int* p;
		p = 0;

		printf("在test2()函数中，调用test1()函数之前\n");
		test1();
		printf("在test2()函数中，调用test1()函数之后\n");
		printf("\n");


		// 下面的语句被执行，将导致一个异常
		*p = 45;

		printf("在test2()函数中，这里将不会被执行到\n");
	}

	SEH_EPILOGUE();
}

void test3()
{
	SEH_PROLOGUE(my_RaiseException_Handler);

	{
		// 下面的语句被执行，将导致一个异常
		RaiseException(0x999, 0x888, 0, 0);

		printf("在test3()函数中，这里将不会被执行到\n");
	}

	SEH_EPILOGUE();
}

int main4()
{
	printf("在main()函数中，调用test1()函数之前\n");
	test1();
	printf("在main()函数中，调用test1()函数之后\n");

	printf("\n");

	printf("在main()函数中，调用test2()函数之前\n");
	test2();
	printf("在main()函数中，调用test2()函数之后\n");

	printf("\n");

	printf("在main()函数中，调用test3()函数之前\n");
	test3();
	printf("在main()函数中，调用test3()函数之后\n");

	return 0;
}