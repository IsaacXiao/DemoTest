#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <regex> 
#include <stdlib.h> // for abs求绝对值

bool CheckValid(const std::string &date)
{
    //若要严谨还需做语义检查，比如一年不可能有15个月，1个月不可能有34天
    //需过滤如2020-15-34这样的非法输入
    //这里纯粹为了做题，仅照指定的格式做正则匹配而已
	const std::regex reg("\\d{4}-\\d{2}-\\d{2}");
	return std::regex_match(date, reg);
}

std::string Time2Str11(const std::chrono::system_clock::time_point& tp)
{
    //3类time_point里，只有system_clock可以转换成time_t，其他不具备可移植性
    // convert to system time:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);    // 这得到的是考虑了时区的时间
    //std::string ts = std::asctime(gmtime(&t));    //这得到的是全球标准时间
    ts.resize(ts.size()-1);             // skip trailing newline
    return ts; 
}

// convert calendar time to timepoint of system clock
//inline
std::chrono::system_clock::time_point
Str2Time11(const char * szTime, std::string time_format = "%4d-%2d-%2d %2d:%2d:%2d")
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
	return std::chrono::system_clock::from_time_t(t);
}

long GetDiffTime11(const std::string &date)
{
	const std::string precise = date + "24:00:00";
	auto when = Str2Time11(precise.c_str());
	auto now = std::chrono::high_resolution_clock::now();
	
	auto elapse = std::chrono::duration_cast<std::chrono::hours/*seconds*/>((when-now));
	return elapse.count();
}

long RoundResult(time_t diff)
{
	constexpr long halfhour = 1800;
    auto remnant = diff % 3600; //算下不足1个小时的零头有多少秒
	return remnant > halfhour ? (diff / 3600 + 1) : (diff / 3600);
}

extern "C" void GetHours(const std::string &date)
{
	//1. 验证参数的有效性
	if ( !CheckValid(date) )
	{
        std::cerr << "GetHours: Invalid Input Param!" << std::endl;
		return;
	}
	//2. 计算时间差的绝对值,因为传进来的时间有可能是过去或者未来
	auto diff = abs(GetDiffTime11(date));
	//3. 对结果做四舍五入
	//auto res = RoundResult(diff);

	std::cout << "__FUNCTION__:\t" << __FUNCTION__  << ": " << diff << std::endl;
}

int main(int argc, char *argv[])
{
    std::string date_input;
    std::cout << "please enter date:" << std::endl;
    std::cin >> date_input;

    GetHours(date_input);

	return 0;
}



