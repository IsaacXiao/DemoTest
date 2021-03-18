#include <iostream>
#include <thread>

using namespace std;

int main() 
{
    std::thread t([]()
    {
        while (true)
        {
            std::cout << "hello..." << std::endl;
            std::this_thread::sleep_for(1000ms);
        }
    });
    std::this_thread::sleep_for(1000ms);    //确保子线程先运行起来
    cout << "xxx" << endl;
    t.join();
    cout << "ooo" << endl;
    return 0;
}

