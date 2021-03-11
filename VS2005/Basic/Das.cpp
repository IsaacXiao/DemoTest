#include <boost/regex.hpp> 
#include <locale> 
#include <iostream> 
#include <string>
#include <typeinfo>
#include <boost/tokenizer.hpp> 
#include <boost/algorithm/string.hpp> 
#include <boost/algorithm/string/regex.hpp> 
#include <boost/format.hpp> 
#include <vector>
#include <boost/tokenizer.hpp> 

#include "FuncHeader.h"

using namespace std;

#define PR(x) cout << endl << "ex: " << #x << "\n";

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
typedef unsigned int UINT;

struct DataPoint
{
	DataPoint( string & name, float value)
	{
		m_strName = name;
		m_fValue = value;
		time(&m_iTime);
	}

	string m_strName;	//变量名称
	time_t m_iTime;	//采集时间
	float m_fValue;		//字段值
};

int main( )
{
	//string strTest( "&*MFLOW*2007*8*19*0*11*30*Nkm3/h*N*0.000*^2403$&*test*1111*2*33*4*55*66*KKK3/x*X*0.000*^9999$" );
	string strTest( "FFFFFFFF;A;116;1621.64;138.06;153.94;171.78;187.26;203.79;218.64;0;339.56;384.83;425.14;449.02;496.16;529.96;578.95;609.03;339.56;382.35;417.7;451.19;158.28;-0.38;-0.38;-0.37;-0.37;3.13;15.84;15.84;104.57;-67.19;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;" );
	//指定分隔符
	//类 boost::char_separator 的构造函数可以接受三个参数， 只有第一个是必须的，它描述了需要隐藏的分隔符。 在本例中， 空格仍然被视为分隔符。
	boost::char_separator<char> sep_points(";"); 
	tokenizer tok_points(strTest, sep_points); 

	vector<DataPoint> vec_DataPt_;
	vec_DataPt_.clear();

	tokenizer::iterator it_points = tok_points.begin();

	int iChannel;
	float fValue;

	//std::cout << *it_points << std::endl; 	
	
	//约定的数据头
	if ( *it_points != "FFFFFFFF" )
	{
		//数据报文格式不对
	}
	else
	{
		it_points++;
		if ( *it_points != "A" )
		{
			//A:机组编号,(全发采集站数据时候,不用考虑)
		}
		else
		{
			//通道个数
			it_points++;
			iChannel = str_to_number<int,string>(*it_points);

			cout << iChannel << endl;

			while( ++it_points != tok_points.end() )
			{
				fValue = str_to_number<float,string>( *it_points );
				cout << fValue << endl;
			}
		}
	}

	return 0;
}

