#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
 
using namespace std::chrono;
 
std::string fetchDataFromDB(std::string recvData) 
{
	std::cout << "fetchDataFromDB start" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(seconds(5));
	return "DB_" + recvData;
}
 
std::string fetchDataFromFile(std::string recvData) {
 
	std::cout << "fetchDataFromFile start" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(seconds(3));
	return "File_" + recvData;
}
 
int main() 
{
	std::cout << "main start" << std::this_thread::get_id() << std::endl;
 
	//获取开始时间
	system_clock::time_point start = system_clock::now();

	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");

	//从文件获取数据
	std::future<std::string> fileData = std::async(std::launch::deferred, fetchDataFromFile, "Data");
 
	//知道调用get函数fetchDataFromFile才开始执行
	std::string FileData = fileData.get();
	//如果fetchDataFromDB()执行没有完成，get会一直阻塞当前线程
	std::string dbData = resultFromDB.get();
	
	//获取结束时间
	auto end = system_clock::now();
 
	auto diff = duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "Total Time taken= " << diff << "Seconds" << std::endl;
 
	//组装数据
	std::string data = dbData + " :: " + FileData;
 
	//输出组装的数据
	std::cout << "Data = " << data << std::endl;
 
	return 0;
}
 