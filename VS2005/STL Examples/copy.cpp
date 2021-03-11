#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int main_copy(int argc, char **argv)
{
	//char* word = "hello";
	//下面这句话修改常量区的内容会运行出错
	//*word = 'j';
	//cout << word << endl;

	int ia[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//char* ia = "hello_world";
	//下面这句话修改栈区的内容不会运行出错
	copy( ia, ia +10, ostream_iterator<int>( cout, " ") );
	//cout << endl;
	copy( ia + 2, ia + 7, ia );
	copy( ia, ia +10, ostream_iterator<int>( cout, " ") );
	cout << endl;

	return 0;
}