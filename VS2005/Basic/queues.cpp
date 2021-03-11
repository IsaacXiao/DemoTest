#include <iostream>
#include <queue>
#include <string>
using namespace std;
void test_empty()
{
	queue<int> myqueue;
	int sum (0);

	for (int i=1;i<=10;i++) myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}
	cout << "total: " << sum << endl;
}//运行结果： total： 55
void test_pop()
{
	queue<int> myqueue;
	int myint;

	cout << "\nPlease enter some integers (enter 0 to end):\n";

	do
	{
		cin >> myint;
		myqueue.push (myint);
	} while (myint);

	cout << "myqueue contains: ";
	while (!myqueue.empty())
	{
		cout << " " << myqueue.front();
		myqueue.pop();
	}
}
/********
运行结果：
Please enter some integers (enter 0 to end):
512
605
420
517
532
0
myqueue contains:  512 605 420 517 532 0
********/
void test_size()
{
	queue<int> myints;
	cout << "0. size: " << (int) myints.size() << endl;

	for (int i=0; i<5; i++) myints.push(i);
	cout << "1. size: " << (int) myints.size() << endl;

	myints.pop();
	cout << "2. size: " << (int) myints.size() << endl;
}
/****
运行结果：
0. size: 0
1. size: 5
2. size: 4
****/
int main()
{
	test_empty();
	cout<<"\n***********************************************\n";
	test_size();
	cout<<"\n***********************************************\n";
	test_pop();
	cout<<"\n***********************************************\n";
	queue<string> q;

	// insert three elements into the queue
	q.push("These ");
	q.push("are ");
	q.push("more than ");
	//cout << "number of elements in the queue: " << q.size()<< endl;

	// read and print two elements from the queue
	cout << q.front();
	q.pop();
	cout << q.front();
	q.pop();
	//cout << "number of elements in the queue: " << q.size()<< endl;

	// insert two new elements
	q.push("four ");
	q.push("words!");
	//cout << "\nnumber of elements in the queue: " << q.size()<< endl;
	// skip one element
	q.pop();

	// read and print two elements
	cout << q.front();
	q.pop();
	cout << q.front() << endl;
	q.pop();

	// print number of elements in the queue
	cout << "number of elements in the queue: " << q.size()<< endl;
}
/*******
*运行结果：
total: 55

***********************************************
0. size: 0
1. size: 5
2. size: 4

***********************************************

Please enter some integers (enter 0 to end):
512
605
420
517
532
0
myqueue contains:  512 605 420 517 532 0
***********************************************
These are four words!
number of elements in the queue: 0

Process returned 0 (0x0)   execution time : 33.512 s
Press any key to continue.

********/
