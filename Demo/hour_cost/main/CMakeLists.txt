

cmake_minimum_required (VERSION 3.8)

project("main")

SET(CMAKE_BUILD_TYPE "Debug") # 这里Type配置为Debug
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")  # Debug模式下的编译指令
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")         # Release模式下的编译指令



#指定生成的是可执行文件
add_executable (${PROJECT_NAME} "main.cpp")




#指定要链接的库
target_link_libraries(${PROJECT_NAME} slow)
#target_link_libraries(${PROJECT_NAME} slow dl) 如果是Linux环境貌似要加dl
