#include <iostream>
using namespace std;
#include "string"
#include "list"

/*
class GoogleOS;

//观察者 
class AndroidUser
{
public:
	AndroidUser(GoogleOS *secretary)
	{
		this->m_secretary = secretary;
	}
	void update(string action)
	{
		cout << "更新系统补丁版本号: " << action << endl;
	}
private:
	GoogleOS *m_secretary;
};
//Subject/ConcreateSubject
class GoogleOS
{
public:
	GoogleOS()
	{
		m_list.clear();
	}
	void Notify(string info)
	{
		//给所有的 观察者 发送 情报
		for ( list<AndroidUser *>::iterator it=m_list.begin(); it!=m_list.end(); it++)
		{
			(*it)->update(info); //
		}
	}

	void setPlayserObserver(AndroidUser *o)
	{
		m_list.push_back(o);
	}

private:
	list<AndroidUser *> m_list;
};

void main()
{
	GoogleOS		*secretary = NULL;
	AndroidUser		*po1 = NULL;
	AndroidUser		*po2 = NULL;

	secretary = new GoogleOS;
	po1 = new AndroidUser(secretary);
	po2 = new AndroidUser(secretary);

	secretary->setPlayserObserver(po1);
	secretary->setPlayserObserver(po2);

	secretary->Notify("2.3.4") ;
	secretary->Notify("4.3.0");
	delete secretary ;
	delete po1 ;
	delete po2 ;

	system("pause");
	return ;
}
*/


