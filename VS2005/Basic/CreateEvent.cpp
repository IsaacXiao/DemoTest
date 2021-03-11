#include "iostream"
#include "windows.h"
using namespace std;

DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
HANDLE hEvent = NULL;
HANDLE hThread1 = NULL;
HANDLE hThread2 = NULL;
int main(int argc, char *args[])
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //使用手动重置为无信号状态，初始化时有信号状态
	//hEvent = CreateEvent(NULL, FALSE, TRUE, NULL); //当一个等待线程被释放时，自动重置为无信号状态，初始是有信号状态
	//if (SetEvent(hEvent))
	//{
	//	cout << "setEvent 成功" <<endl;
	//}
	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc1, NULL, 0,NULL);
	Sleep(200);
	hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc2, NULL, 0,NULL);
	Sleep(200);
	if ( NULL == hThread1 )
	{
		cout <<"create thread fail!";
	}
	if ( NULL == hThread2 )
	{
		cout <<"create thread fail!";
	}
	//DWORD dCount = ResumeThread(hThread);
	//cout << LOWORD(dCount) << endl;
	return 0;
}
DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	cout <<"in thread1@!"<<endl;

	DWORD dReturn = WaitForSingleObject(hEvent,INFINITE);

	if ( WAIT_OBJECT_0 == dReturn)
	{
		cout <<" thread1 signaled ! "<<endl;
	}
	cout <<"in thread1 --signal"<<endl;

	//SetEvent(hEvent);
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	cout <<"in thread2@!"<<endl;

	DWORD dReturn = WaitForSingleObject(hEvent,INFINITE);

	if ( WAIT_OBJECT_0 == dReturn)
	{
		cout <<"thread2 signaled ! "<<endl;
	}
	cout <<"in thread2--signal"<<endl;

	//SetEvent(hEvent);
	return 0;
}
