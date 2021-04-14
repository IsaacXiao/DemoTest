

cmake_minimum_required (VERSION 3.8)

project ("hour_cost")

SET(CMAKE_BUILD_TYPE "Debug") # 这里Type配置为Debug
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")  # Debug模式下的编译指令
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")         # Release模式下的编译指令

#把所有编译结果都统一输出到bin目录下，方便管理或调试
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include sub-projects.
add_subdirectory ("hour")
add_subdirectory ("slow")
add_subdirectory ("cost")
add_subdirectory ("main")


