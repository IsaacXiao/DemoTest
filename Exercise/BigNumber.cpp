//用双向链表实现大数加减法，效果如帖子所描述的一样
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

class BitNum
{
	int num;
	bool carry;	//标识是否产生进位或者借位
	BitNum( int n = 0, bool c = false ): num( n ), carry( c ){ }
	BitNum & operator+=( int n )
	{
		num += n;
		return *this;
	}
	BitNum & operator-=( int n )
	{
		num -= n;
		return *this;
	}
};

class BigNum
{
	bool negative; //标识是否为负数
	
public:
	list<BitNum> list_bn;
	BigNum( ): list_bn( list<BitNum>( ) ), negative( false ){ }
	//用n个0初始化
	BigNum( size_t n,  BitNum  bn ): list_bn( n, bn ),negative( false ){ }
	BigNum( string & str_num )
	{
		negative = false;
		//这里就懒得处理非法输入的异常了
		//从高位到低位输入
		string::iterator it = str_num.begin();
		if ( '-' == *it )	//最高位为-则为负数
		{
			negative = true;
			++it;		//前++效率更高
		}
		for ( ; it != str_num.end(); it++ )
		{
			//单个字符转换成数字
			int n = (*it) - '0';
			BitNum bitn( n, false );
			list_bn.push_back( bitn );
		}
	}
	bool IsNegative( ) const { return negative; }
	//list<BitNum> GetList( ) const { return list_bn; }
	size_t Len( ) const { return list_bn.size( ); }
};

//减法懒得写了
BigNum operator-( const BigNum & b1, const BigNum & b2 )
{
	return BigNum( );
}

//为BitNum实现+运算符，加的结果判断是否大于等于10，若是则设置carry为true表示带了一位到链表的下一个节点，把该结果模10求余数存到链表的节点里
BitNum operator+( const BitNum & b1, const BitNum & b2 )
{
	int num = b1.num + b2.num;
	if ( num < 10)
	{
		return BitNum( num, false );
	} 
	else
	{
		num = num % 10;
		return BitNum( num, true );
	}
}

BigNum operator+( const BigNum & b1, const BigNum & b2 )
{
	if ( b1.IsNegative() ^ b2.IsNegative() )	//一正一负则做减法
	{
		return operator-( b1, b2 );
	} 
	else
	{
		//考虑2个数的位数可能会不一样，先从简单的情况开始试一下，如46295+36
		size_t len_max = __max( b1.Len( ), b2.Len( ) );
		size_t len_min = __min( b1.Len( ), b2.Len( ) );
		//以位数较多的构造result，结果放到result里
		BigNum result = BigNum( len_max, BitNum( 0, false ) );
		list<BitNum>::iterator it_res = result.list_bn.begin();
		advance( it_res, len_max - 1 );	//指向最后一个节点，也就是个位数
		list<BitNum>::const_iterator it1 = b1.list_bn.begin();
		advance( it1, b1.Len( )-1 );		//指向最后一个节点，也就是个位数
		list<BitNum>::const_iterator it2 = b2.list_bn.begin();
		advance( it2, b2.Len( )-1 );	//指向最后一个节点，也就是个位数
		
		//先算95+36
		//从低位到高位做加法
		for( size_t i = 0; i < len_min; i++ )
		{
			//因为it_res的所有位只可能是0，为1则意味着是低位进上来的
			if ( it_res->num == 1 )
			{
				*it_res = *it1 + *it2;
				*it_res += 1;
			} 
			else
			{
				*it_res = *it1 + *it2;
			}
			
			if ( it1 != b1.list_bn.begin() )
			{
				it1--;
			}
			if ( it2 != b2.list_bn.begin() )
			{
				it2--;
			}
			//如果该位产生了进位
			if ( it_res->carry )
			{
				it_res--;
				//则它的更高一位加1
				*it_res += 1;
			}
			else
				it_res--;
		}
		//这时候it1与it2中的其中一个肯定到达begin了
		list<BitNum>::const_iterator it_tmp;
		if ( it1 == b1.list_bn.begin() )
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
			*it_res = *it_res + *it_tmp;
			if ( it_res != result.list_bn.begin() )
			{
				it_tmp--;
				it_res--;
			}
		}
		//最高位有可能会产生进位
		if ( it_res->carry )
		{
			result.list_bn.push_back( BitNum( 1, false ) );
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

	for ( list<BitNum>::iterator it = res.list_bn.begin(); it != res.list_bn.end(); ++it )
	{
		cout << it->num;
	}
	cout << endl;

	return 0;
}