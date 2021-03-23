#include <iostream>
using namespace std;

class Person
{
private:
	void SayHello( )
	{
		cout << "ÄãºÃ" << endl;
	}
	void SayGoodbye( )
	{
		cout << "ÔÙ¼û" << endl;
	}
protected:
	typedef void ( Person::*vSay )( );
	vSay vFun[2];
	unsigned age;
public:
	Person()
	{
		vFun[0] = &Person::SayHello;
		vFun[1] = &Person::SayGoodbye;
	}
	void virtualHello( )
	{
		(this->*vFun[0])();
	}
	void virtualGoodbye( )
	{
		(this->*vFun[1])();
	}
};

class Student : public Person
{
private:
	void SayHello( )
	{
		cout << "Hello" << endl;
	}
	void SayGoodbye( )
	{
		cout << "Goodbye" << endl;
	}
protected:
	/*typedef void ( Student::*vSay )( );
	vSay vFun[2];*/
public:
	Student()
	{
		vFun[0] = (Person::vSay)&Student::SayHello;
		vFun[1] = (Person::vSay)&Student::SayGoodbye;
	}
	void virtualHello( )
	{
		(this->*vFun[0])();
	}
	void virtualGoodbye( )
	{
		(this->*vFun[1])();
	}
};

int main(int argc, char **argv)
{
	Person * p = NULL;

	p = new Person;
	p->virtualHello();
	p->virtualGoodbye();
	delete p;

	p = new Student;
	p->virtualHello();
	p->virtualGoodbye();
	delete p;

	return 0;
}
