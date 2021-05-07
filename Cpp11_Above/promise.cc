//https://blog.csdn.net/godmaycry/article/details/72844159

#include <iostream>
#include <future>
#include <chrono>
#include <functional>
 
//声明一个可调对象
using FncT = std::function<int(int)>;		
 
int Test_Fun(int iVal)
{
	std::cout << "Value is:" << iVal << std::endl;
	return iVal + 232;
}
 
void Thread_Fun1(std::promise<FncT> &p)
{
	//为了突出效果，可以使线程休眠5s
	std::this_thread::sleep_for(std::chrono::seconds(5));
 
	std::cout << "传入函数Test_Fun" << std::endl;
 
	//传入函数Test_Fun
	//p.set_value(std::bind(&Test_Fun, std::placeholders::_1));
	p.set_value([](int iVal) ->int
		{
			std::cout << "Value is:" << iVal << std::endl;
			return iVal + 999;			
		}
	);
}
 
void Thread_Fun2(std::future<FncT> &f)
{
	//阻塞函数，直到收到相关联的std::promise对象传入的数据
	auto fun = f.get();		//iVal = 233
 
	int iVal = fun(1);
 
	std::cout << "收到函数并运行，结果：" << iVal << std::endl;
}
 
int main()
{
	//声明一个std::promise对象pr1，其保存的值类型为FncT
	std::promise<FncT> pr1;
	//声明一个std::future对象fu1，并通过std::promise的get_future()函数与pr1绑定
	std::future<FncT> fu1 = pr1.get_future();
 
	//创建一个线程t1，将函数Thread_Fun1及对象pr1放在线程里面执行
	std::thread t1(Thread_Fun1, std::ref(pr1));
	//创建一个线程t2，将函数Thread_Fun2及对象fu1放在线程里面执行
	std::thread t2(Thread_Fun2, std::ref(fu1));
 
	//阻塞至线程结束
	t1.join();
	t2.join();
 
	return 1;
}