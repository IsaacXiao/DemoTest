#include <iostream>
using namespace std;

int ExceptionFilter(int& s) 
{
	cout << "exception filter with s = " << s << endl;
	s++;
	return -1; // EXCEPTION_CONTINUE_EXECUTION
}

void SEHtest()
{
	int s = 0;
	__try
	{
		cout << "before exception" << endl;
		int j = 1 / s;
		cout << "after exception" << endl;
	} __except(ExceptionFilter(s)) 
	{
		cout << "exception handler" << endl;
	}
	cout << "after try-catch" << endl;
	return;
}

int main6()
{
	SEHtest();
	return 0;
}