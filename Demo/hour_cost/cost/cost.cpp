#include <iostream>
//#include <unistd.h>
#include <stdlib.h>
#include <chrono>

void SlowFunc();

#define WIN32

#ifdef WIN32
#define COST_FUNC __declspec(dllexport)
#endif // WIN32


extern "C" COST_FUNC void GetCost(const char* date)
{
	auto begin = std::chrono::high_resolution_clock::now();
	SlowFunc();
	auto end = std::chrono::high_resolution_clock::now();
	auto elapse = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	std::cout << "__FUNCTION__:\t" << __FUNCTION__ << ", cost: " << elapse.count() << std::endl;
}

#if 0
//简单测试一下
int main(int argc, char *argv[])
{
    GetCost(std::string("dumb"));

	return 0;
}
#endif

#ifdef WIN32
#include <Windows.h>
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	return TRUE;
}
#endif // WIN32