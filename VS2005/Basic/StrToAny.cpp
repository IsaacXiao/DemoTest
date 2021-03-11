#include <iostream>  
using namespace std;

#include <boost/lexical_cast.hpp>

#define INNER_ERROR_NUMBER -99999

#define ERROR_LEXICAL_CAST     1 

template<typename T, typename StrT>
T str_to_number( StrT value )
{
	T d;
	try
	{
		d = boost::lexical_cast<T>(value);
		return d;
	}
	catch( boost::bad_lexical_cast ex )
	{
		return (T)INNER_ERROR_NUMBER;
	}
}

template<typename T>
bool StrToAny( const std::string& str_value, T* rhs )
{		
	if( rhs == NULL || str_value.size() == 0 )
		return false;
	T value = str_to_number<T,std::string>( str_value );
	*rhs = value;
	return true;
}

template<>
bool StrToAny<std::string>( const std::string& str_value, std::string* rhs ){		
	if( rhs == NULL || str_value.size() == 0 )
		return false;			
	rhs->assign(str_value);
	return true;
}	

template<>
bool StrToAny<bool>( const std::string& str_value, bool* rhs )
{		
	short n;
	if( StrToAny<short>( str_value, &n ) == false )
		return false;
	*rhs = n > 0;
	return true;
}

int main()
{
	using boost::lexical_cast;
	int         a = 0;
	double        b = 0.0;
	std::string s = ""; 
	int            e = 0;    
	try
	{ 
		// ----- 字符串 --> 数值 
		a = lexical_cast<int>("123");
		b = lexical_cast<double>("123.12");
		// ----- 数值 --> 字符串
		s = lexical_cast<std::string>("123456.7"); 
		// ----- 异常处理演示
		/*e = lexical_cast<int>("abc");*/
	}
	catch(boost::bad_lexical_cast& e)
	{
		// bad lexical cast: source type value could not be interpreted as target
		std::cout << e.what() << std::endl;
		return ERROR_LEXICAL_CAST;
	} 

	std::cout << a << std::endl;    // 输出：123 
	std::cout << b << std::endl;    // 输出：123.12 
	std::cout << s << std::endl;     // 输出：123456.7 

	return 0;
}
