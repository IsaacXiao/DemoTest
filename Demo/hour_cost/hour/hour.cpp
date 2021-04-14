#include <iostream>
#include <string>
#include <regex>    
#include <time.h>   // for time
#include <stdlib.h> // for abs�����ֵ

inline bool CheckValid(const std::string &date)
{
    //��Ҫ�Ͻ������������飬����һ�겻������15���£�1���²�������34��
    //�������2020-15-34�����ķǷ�����
    //���﴿��Ϊ�����⣬����ָ���ĸ�ʽ������ƥ�����
	const std::regex reg("\\d{4}-\\d{2}-\\d{2}");
	return std::regex_match(date, reg);
}

time_t StrToTime(const char * szTime, std::string time_format = "%4d-%2d-%2d %2d:%2d:%2d")
{
	struct tm tm1;
	time_t t;
	memset(&tm1, 0, sizeof(tm));		
	sscanf(szTime, time_format.c_str(),
		&tm1.tm_year,
		&tm1.tm_mon,
		&tm1.tm_mday,
		&tm1.tm_hour,
		&tm1.tm_min,
		&tm1.tm_sec);
	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	t = mktime(&tm1);
	return t;
}

time_t GetDiffTime(const std::string &date)
{
    const std::string precise = date + "24:00:00";
	auto when = StrToTime(precise.c_str());

	time_t now;
	time(&now);

	//���Ͻ����������ֵ��������difftime����⺯��
	//��Ϊ��������ʱ���п����ǹ�ȥ����δ��
	return abs(when - now);
}

time_t RoundResult(time_t diff)
{
	constexpr long halfhour = 1800;
    auto remnant = diff % 3600; //���²���1��Сʱ����ͷ�ж�����
	return remnant > halfhour ? (diff / 3600 + 1) : (diff / 3600);
}

#define WIN32

#ifdef WIN32
#define HOUR_FUNC __declspec(dllexport)
#endif // WIN32


extern "C" HOUR_FUNC void GetHours(const char* date)
{
	std::cout << date << std::endl;
	//1. ��֤��������Ч��
	if ( !CheckValid(std::string(date)) )
	{
        std::cerr << "GetHours: Invalid Input Param!" << std::endl;
		return;
	}
	//2. ����ʱ���ľ���ֵ
	auto diff = GetDiffTime(std::string(date));
	//3. �Խ������������
	auto res = RoundResult(diff);

	std::cout << "__FUNCTION__:\t" << __FUNCTION__  << ": " << res << std::endl;
}

#if 0
//�򵥲���һ��
int main(int argc, char *argv[])
{
    std::string date_input;
    std::cout << "please enter date:" << std::endl;
    std::cin >> date_input;

    GetHours(date_input);

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