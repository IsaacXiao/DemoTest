#ifndef WIN32_HEADER_H
#define WIN32_HEADER_H

#include <string>
#include <iostream>
#include <windows.h>


typedef HINSTANCE SO_HANDLE;    //增加可读性

//资源管理类
struct SoManager
{
    SoManager( const std::string& file_name ) : file_name_( file_name )
    {
		std::cout << file_name << std::endl;
        handle_ = LoadLibraryA( file_name.c_str() );
    }
    bool IsValid() const
    {
        return nullptr!=handle_;
    }
    auto GetFunc( const std::string& func_name ) const
    {
        return GetProcAddress( handle_, func_name.c_str() );
    }
    const std::string& FileName() const //为类提供内省机制
    {
        return file_name_;
    }
    ~SoManager()
    {
        if(IsValid())
        {
              FreeLibrary( handle_ );
              std::cout << "so has released" << std::endl;      
        }
    }
private:
    SO_HANDLE	handle_;
    std::string	file_name_;
};

#endif

