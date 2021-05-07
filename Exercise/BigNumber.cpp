
//https://blog.csdn.net/VonSdite/article/details/78037269
//https://blog.csdn.net/qq_37193603/article/details/72900259
#include <list>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <stack>
using namespace std;

template<typename ItorT>
void print_container(const ItorT first, const ItorT last, const char* separate = "") noexcept
{
	//typedef typename iterator_traits<ItorT>::value_type Ty;
	std::copy( first, last, std::ostream_iterator<decltype(*first)>( std::cout, separate ) );
	//std::cout << std::endl;
}

constexpr bool NO_CARRY = false;
constexpr bool CARRY = true;

struct Bit
{
	int num_{0};
	bool carry_{false};	

	Bit( int n = 0, bool c = false ): num_( n ), carry_( c ){ }
	Bit & operator+=( int n )
	{
		num_ += n;
		if (num_<10)
		{
			carry_ = false;
		}
		else
		{
			num_ = num_%10;
			carry_ = true;
		}
		
		return *this;
	}
	Bit & operator+=( Bit && rb )
	{
		num_ += rb.num_;
		carry_ = rb.carry_;
		return *this;
	}
};

ostream& operator<<(ostream &os,const Bit &bit)
{
	os << bit.num_ << endl;
	return os;
}

Bit operator+( const Bit & b1, const Bit & b2 )
{
	int num = b1.num_ + b2.num_;
	if ( num < 10)
	{
		return Bit( num, false );
	} 
	else
	{
		num = num % 10;
		return Bit( num, true );
	}
}

class BigNum
{
	friend BigNum operator+( const BigNum & num1, const BigNum & num2 );
private:	
	bool negative_{false}; 
	list<Bit> bit_num_;
public:
	BigNum( ): bit_num_( list<Bit>( ) ), negative_( false ){ }
	BigNum( size_t n,  Bit bn ): bit_num_( n, bn ),negative_( false ){ }
	BigNum( const string & str_num )
	{
		//这里就懒得处理非法输入的异常了
		//从高位到低位输入
		string::const_iterator it = str_num.begin();
		if ( '-' == *it )//最高位为-则为负数
		{
			negative_ = true;
			++it;
		}
		for ( ; it != str_num.end(); it++ )
		{
			int n = (*it) - '0';
			bit_num_.emplace_back(n,false);
		}
	}
	bool IsNegative( ) const { return negative_; }
	size_t Len( ) const { return bit_num_.size( ); }
	void Display() const 
	{ 
		cout << boolalpha << negative_ << ":" << endl;
		print_container(bit_num_.begin(),bit_num_.end(),"");
	}
};

//为BitNum实现+运算符，加的结果判断是否大于等于10，若是则设置carry为true表示带了一位到链表的下一个节点，把该结果模10求余数存到链表的节点里
BigNum operator+( const BigNum & num1, const BigNum & num2 )
{
	if ( num1.IsNegative() ^ num2.IsNegative() )	
	{
		//return operator-( b1, b2 );//减法懒得写了
	} 
	else
	{
		//考虑2个数的位数可能会不一样，先从简单的情况开始试一下，如46295+36
		size_t len_max = __max( num1.Len( ), num2.Len( ) );
		size_t len_min = __min( num1.Len( ), num2.Len( ) );
		//以位数较多的构造result，结果放到result里
		BigNum result = BigNum( len_max+1, Bit( 0, NO_CARRY ) );
		list<Bit>::iterator bit_res = result.bit_num_.begin();
		advance( bit_res, len_max );	//指向最后一个节点，也就是个位数
		list<Bit>::const_iterator it1 = num1.bit_num_.begin();
		advance( it1, num1.Len( )-1 );		
		list<Bit>::const_iterator it2 = num2.bit_num_.begin();
		advance( it2, num2.Len( )-1 );	
		
		auto pre = bit_res;
		//先算95+36
		//从低位到高位做加法
		for( size_t i = 0; i < len_min; i++ )
		{
			if (true==pre->carry_)
			{
				*bit_res += 1;
			}
			*bit_res += (*it1-- + *it2--);
			pre = bit_res--;	
		}
		if (true==pre->carry_)
		{
			*bit_res += 1;
		}

		//这时候it1与it2中的其中一个肯定到达begin了
		list<Bit>::const_iterator it_tmp;
		if ( it1 == num1.bit_num_.begin() )
		{
			it_tmp = it2;
		} 
		else	//it2 == b2.GetList().begin() 
		{
			it_tmp = it1;
		}
		//再算462+剩余的0
		for ( size_t j = len_min + 1; j <= len_max; j++ )
		{
			*bit_res = *bit_res + *it_tmp;
			if ( bit_res != result.bit_num_.begin() )
			{
				it_tmp--;
				bit_res--;
			}
		}
		//最高位有可能会产生进位
		if ( bit_res->carry_ )
		{
			result.bit_num_.emplace_back( 1, false );
		}
		return result;
	}
}

int main( ) 
{
	string str1, str2;
	cin >> str1 >> str2;
	cout << "calc..........." << endl;
	BigNum b1( str1 );
	BigNum b2( str2 );
	BigNum res = b1 + b2;

	res.Display();

	return 0;
}