

cmake_minimum_required (VERSION 3.8)
project("slow")

SET(CMAKE_BUILD_TYPE "Debug") # 这里Type配置为Debug
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")  # Debug模式下的编译指令
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")         # Release模式下的编译指令

#指定生成的是静态库
add_library (${PROJECT_NAME} STATIC "slow.cpp")

#PIC：position independent code
#PRIVATE：the directory is added to this target's include directories
target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC") #在Linux下需要加上-fPIC



