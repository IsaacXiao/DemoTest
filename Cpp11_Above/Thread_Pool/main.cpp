
#include <mutex>
#include "product.h"
#include <unordered_set>

//这个地方做成全局的或者用别的方式让AlgProcessThread类和S7通信类都要能访问到
std::unordered_set<Product> g_img_stash;
std::mutex g_mut;

class AlgProcessThread
{
public:
    void run()
    {
        ///自己编号给个ID从1开始即可
        size_t id = 1;
        ///调用算法函数获取结果
        ///auto res = processDomesticDefect
        RESULT res = RESULT::TBA;
        ///获取当前时间
        TimeType now = std::chrono::high_resolution_clock::now();
        
        //1. 处理线程是生产者！！！！
        g_mut.lock();
        g_img_stash.emplace(id,now,res);
        g_mut.unlock();
    }
};

//自定义的S7协议通信类
class Snap7Client
{
public:
    //写个校验方法
    void Check()
    {
        //2. 主线程是消费者！！！
        g_mut.lock();
        //下面这个product是构造一下模拟来自PLC
        TimeType now = std::chrono::high_resolution_clock::now();
        size_t id = 9999;
        auto product = Product(9999,now,RESULT::TBA);
        auto which = g_img_stash.find(product);
        if (which!=g_img_stash.end())
        {
            //把*which返回给PLC
        }
        else
        {
            //把这个product返回给PLC
        }
        g_mut.unlock();
    }
};

class MetalCircularRingInspection
{
    Snap7Client s7_;
public:
    void Check()
    {
        s7_.Check();
    }
};


int main(int argc,char** argv)
{
    // MetalCircularRingInspection w;
    // w.show();

    return 0;
}