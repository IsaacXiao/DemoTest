#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp> 

int main()
{
	/*
	string s="GD_CUS_STATE_20160505_164930_PAS_RTNET";
	
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
	//指定分隔符
	boost::char_separator<char> sep("_"); 
	tokenizer tok(s, sep); 
	string filedate("");
	int i = -1;
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) 
	{
		i++;
		string tmp(*it);
		//cout << tmp << endl;
		if ( i == 3 || i == 4 )
		{
			filedate += tmp;
		}
	}
	cout << filedate << endl;
	*/

	/*
	string pt_Info("#        沙角C厂        122723090013627617        #1发电机出口一氧化碳浓度        0        0        ");

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
	//指定分隔符
	boost::char_separator<char> sep(" "); 
	tokenizer tok(pt_Info, sep); 
	
	string fac_name("");
	string pt_id("");
	string pt_name("");
	string pt_value("");
	string pt_state("");

	int i = -1;
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) 
	{
		i++;
		cout << i << ":\t" << *it << endl;

		//string tmp(*it);
		switch( i )
		{
		case 1:
			 fac_name = *it;
			 break;
		case 2:
			 pt_id = *it;
			 break;
		case 3:
			 pt_name = *it;
			 break;
		case 4:
			 pt_value = *it;
			 break;
		case 5:
			 pt_state = *it;
			 break;
		}
	}
	*/

	string str1( "Alpha Beta Gamma Delta" );
	unsigned int loc = str1.find( "Gamma", 0 );
	if( loc != string::npos )
		cout << "Found Gamma at " << loc << endl;
	else
		cout << "Didn't find Gamma" << endl;


	return 0;
}
