
#include <boost/asio.hpp> 
#include <iostream> 
#include <string> 
#include <boost/regex.hpp>

using namespace std;

int main( )
{
	string sZip( "afa\"grundlagen/Allgemeine Grundlagen der Programmierung.zip\"afa" );
	
	boost::regex expr( "\"[\\w\\/\\\ \\d]+\\w\\.zip\"" );
	boost::smatch what;

	boost::cmatch mat;
	bool r = boost::regex_match(sZip, expr);

	if (boost::regex_search(sZip, what, expr)) 
	{ 
		std::cout << what[0] << std::endl; 
		std::cout << what[1] << std::endl;
		std::cout << what[2] << std::endl;
	} 

	return 0;
}

/*
#include <boost/asio.hpp> 
#include <iostream> 
#include <string> 
#include <boost/regex.hpp>

using namespace std;

int main( )
{
	const char *str_reg="(\\w+)://((\\w+\\.)*\\w+)((/\\w*)*)(/\\w+\\.\\w+)?";
	const char *str_orig="http://www.allen2660.com/2013/03/10/newcomputer.html";

	boost::cmatch mat;
	boost::regex reg( str_reg);
	//这个regex_match函数多了一个参数
	bool r = boost::regex_match( str_orig, mat , reg);
	if(r)
	{
		cout<< "mat size is "<< mat.size()<<endl;
		typedef boost::cmatch::iterator match_itr;
		match_itr itr = mat.begin();
		while(itr!=mat.end())
		{
			//itr的first和second指向匹配字符串的首位位置
			//cout<< itr->first << ' '<<itr->second << ' '<< *itr<<endl;
			cout<<  *itr<<endl;
			itr++;
		}
	}

	return 0;
}
*/
