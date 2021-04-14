#ifndef LINUX_HEADER_H
#define LINUX_HEADER_H

#include <string>
#include <iostream>
#include <dlfcn.h> 
#include <unistd.h>

void os_sleep(size_t Milliseconds)
{
	return usleep(Milliseconds);
}

typedef void* SO_HANDLE;    //增加可读性

//资源管理类
struct SoManager
{
    SoManager( const std::string& file_name ) : file_name_( file_name )
    {
        handle_ = dlopen( file_name.c_str(), /*RTLD_NOW*/RTLD_LAZY );
    }
    bool IsValid() const
    {
        return nullptr!=handle_;
    }
    void* GetFunc( const std::string& func_name ) const
    {
        return dlsym( handle_, func_name.c_str() );
    }
    const std::string& FileName() const //为类提供内省机制
    {
        return file_name_;
    }
    ~SoManager()
    {
        if(IsValid())
        {
              dlclose( handle_ );
              std::cout << "so的句柄资源释放了" << std::endl;      
        }
    }
private:
    SO_HANDLE	handle_;
    std::string	file_name_;
};

#endif

