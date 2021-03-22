#include "thread_pool.h"
#include <iostream>
#include <functional>
#include "./ThreadSafe_Queue.hpp"
using namespace std;


struct Mediator
{
    //1. 把int替换成cv::mat类型
    ThreadSafe_Queue<int> img_stash_; 
};

Mediator mediator_;

struct ICameraGrabber
{
    int img{0};
    bool IsStoped() const { return stop_; }
    void StopGrabbing() { stop_ = true; }
    virtual void GetImage() = 0;
private:
    bool stop_{false};
};

//2. 把采集逻辑都包到DMKCamera类里面去
struct DMKCamera: public ICameraGrabber
{
    //3. 重写这个虚函数
    void GetImage() override
    {
        while ( !IsStoped() )
        {
            cout << "\n pushing image to stash: " << endl;
            mediator_.img_stash_.push(++img);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
};
    
///下面的main函数调用由我来完成
///我能够把一个int数字拿到控制台显示就能把一张图片拿到ui上显示
int main(int argc,char** argv)
{
    try 
    {
        threadpool executor{ 8 };
        ICameraGrabber * camera = new DMKCamera;
    
        std::future<void> res = executor.commit(std::bind(&ICameraGrabber::GetImage,camera));

        int c;
        while ((c = getchar()) != 'q')
        {
            int img;
            mediator_.img_stash_.wait_and_pop(img);
            cout << "display: " << img << endl;
        }
        camera->StopGrabbing();
        cout << "end grabbing" << endl;
        return 0;
    }
    catch (std::exception& e) 
    {
        std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;

    }
}