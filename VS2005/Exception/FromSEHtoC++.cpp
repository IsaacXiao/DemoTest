#include <windows.h> 
#include <cstdio> 
#include <eh.h> 
#include <string> 
#include <exception> 
using namespace std; 
//////////////////////////////////////////////////////////////////////////////// 
class seh_exception_base : public std::exception 
{ 
public: 
	seh_exception_base (const PEXCEPTION_POINTERS pExp, std::string what ) 
		: m_ExceptionRecord(*pExp->ExceptionRecord), 
		m_ContextRecord(*pExp->ContextRecord), 
		m_what(what){}; 
	~seh_exception_base() throw(){} ; 
	virtual const char* what() const throw() 
	{ 
		return m_what.c_str(); 
	} 
	virtual DWORD exception_code() const throw() 
	{ 
		return m_ExceptionRecord.ExceptionCode; 
	} 
	virtual const EXCEPTION_RECORD& get_exception_record() const throw() 
	{ 
		return m_ExceptionRecord; 
	} 
	virtual const CONTEXT& get_context() const throw() 
	{ 
		return m_ContextRecord; 
	} 
	// 初始化函数 
	static void initialize_seh_trans_to_ce() 
	{ 
		_set_se_translator( trans_func ); 
	} 
	// 系统异常出现时的回调函数 
	static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp ); 
protected: 
	std::string m_what; 
	EXCEPTION_RECORD m_ExceptionRecord; 
	CONTEXT m_ContextRecord; 
}; 
//////////////////////////////////////////////////////////////////////////////// 
// 下面是系统异常被转换后的 C++ 类型的异常 
// 篇幅有限，因此只简单设计了对几种常见的系统异常的转换 
//////////////////////////////////////////////////////////////////////////////// 
class seh_exception_access_violation : public seh_exception_base 
{ 
public: 
	seh_exception_access_violation (const PEXCEPTION_POINTERS pExp, std::string what) 
		: seh_exception_base(pExp, what) {}; 
	~seh_exception_access_violation() throw(){}; 
}; 
//////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////// 
class seh_exception_divide_by_zero : public seh_exception_base 
{ 
public: 
	seh_exception_divide_by_zero (const PEXCEPTION_POINTERS pExp, std::string what) 
		: seh_exception_base(pExp, what) {}; 
	~seh_exception_divide_by_zero() throw(){}; 
}; 
//////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////// 
class seh_exception_invalid_handle : public seh_exception_base 
{ 
public: 
	seh_exception_invalid_handle (const PEXCEPTION_POINTERS pExp, std::string what) 
		: seh_exception_base(pExp, what) {}; 
	~seh_exception_invalid_handle() throw(){}; 
}; 
//////////////////////////////////////////////////////////////////////////////// 
// 系统异常出现时的回调函数 
// 这里是实现，很关键。针对不同的异常，抛出一个 C++ 类型的异常 
void seh_exception_base::trans_func( unsigned int u, EXCEPTION_POINTERS* pExp ) 
{ 
	switch(pExp->ExceptionRecord->ExceptionCode) 
	{ 
	case EXCEPTION_ACCESS_VIOLATION : 
		throw seh_exception_access_violation(pExp, " 存储保护异常 "); 
		break; 
	case EXCEPTION_INT_DIVIDE_BY_ZERO : 
		throw seh_exception_divide_by_zero(pExp, " 被 0 除异常 "); 
		break; 
	case EXCEPTION_INVALID_HANDLE : 
		throw seh_exception_invalid_handle(pExp, " 无效句病异常 "); 
		break; 
	default : 
		throw seh_exception_base(pExp, " 其它 SEH 异常 "); 
		break; 
	} 
} 
// 来测试吧！ 
void main( void ) 
{ 
	seh_exception_base::initialize_seh_trans_to_ce(); 
	try 
	{ 
		// 被 0 除 
		int x, y=0; 
		x = 5 / y; 
		// 存储保护 
		char* p =0; 
		*p = 0; 
		// 其它系统异常，例如中断异常 
		__asm int 3; 
	} 
	catch( seh_exception_access_violation& e ) 
	{ 
		printf( "Caught SEH_Exception. 错误原因： %s/n", e.what()); 
		//other processing 
	} 
	catch( seh_exception_divide_by_zero& e ) 
	{ 
		printf( "Caught SEH_Exception. 错误原因： %s/n", e.what()); 
		//other processing 
	} 
	catch( seh_exception_base& e ) 
	{ 
		printf( "Caught SEH_Exception. 错误原因： %s, 错误代码： %x/n", e.what(), e.exception_code()); 
	} 
} 
