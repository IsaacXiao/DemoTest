#include <iostream>
using namespace std;
#include <string>
#include "print.h"
#include <typeinfo>

typedef unsigned int Uint;

class ME : public exception
{
	char msg[100];
public:
	ME(int n){sprintf(msg,"从第%d行抛出异常",n);}
	ME(char info[100]){strcpy(msg, info);}
	const char*what()const throw(){return msg;}
};

class Array
{
	Uint n;
	pair<string, string>* p; 
public:
	Array():n(1)
	{
		p = new pair<string,string>[1];
		p->first = ""; p->second = "";
		if(p==NULL)throw ME(__LINE__);
	}	
	Array(Uint n):n(n)
	{
		p = new pair<string, string>[n];
		for(Uint i = 0; i < n; i++)
		{
			p->first = ""; p->second = "";
		}
		if(p==NULL)throw ME(__LINE__);
	}	
	Array(const Array& a):p(new pair<string, string>[a.n]),n(a.n)
	{
		copy(a.p, a.p+a.n, p);
	}
	Array& operator=(const Array& a)
	{
		if(this==&a)return *this;
		delete [] p;
		p = new pair<string,string>[a.n];
		n = a.n;
		copy(a.p, a.p+a.n, p);
	}		
	~Array(){	delete [] p;	}	
	Uint size()const{return n;}
	pair<string, string>& operator[](Uint i)const
	{
		if(i>=n)throw ME(__LINE__);
		return p[i];
	}
	string& operator[](string key)
	{
		for(Uint i = 0; i < n; i++)
		{
			if(p[i].first == key)
				return p[i].second;
		}
		for(Uint i = 0; i < n; i++)
		{
			if(p[i].first.empty())
			{
				p[i].first = key;
				return p[i].second;
			}
		}
		pair<string, string>* pOld = p;
		p = new pair<string, string>[n+1];
		copy(pOld, pOld + n, p);
		p[n].first = key;
		delete [] pOld;
		return p[n++].second;		
		//throw ME("没有该键对应的值也无法再增加了！！");		
	}
	friend ostream& operator<<(ostream& out, const Array& arr)
	{
		out << typeid(arr).name() << ":" << endl;
		for(Uint i = 0; i < arr.n; i++)
		{
			if(!arr.p[i].first.empty())
				out << arr[i].first << " => " << arr[i].second << endl;
		}
		return out;
 	}
};

ostream& operator<<(ostream& o, const pair<string,string>& p)
{	
	if(!p.first.empty())
		o << p.first << " => " << p.second << endl;	
	return o;
}

int main()
{
	//Array user(4);
	//Array user(14);
	Array user;
	
	user["id"] = "a001";
	user["name"] = "zhangsan";
	user["pwd"] = "111111";
	user["email"] = "z@163.com";
	
	cout << user << endl;

	Array USERS[3];
	USERS[0] = user;
	cout << USERS[0]["name"] << endl;
	//cout << user[4] << endl;
	cout << user["test"] << endl;
	
	return 0;
}