cmake_minimum_required(VERSION 3.19)
project(cppEssence)

set(CMAKE_CXX_STANDARD 14)

add_executable(cppEssence_05 01_cpp11AndAbove/05_condition_variable.cpp)
add_executable(cppEssence_06 01_cpp11AndAbove/06_thread_01.cpp)
add_executable(cppEssence07 01_cpp11AndAbove/07_thread_local.cpp)

# thread_pool
#add_subdirectory(03_thread_pool)						# 添加math子目录
#add_executable(pool ${ALL_SRCS})	# 指定生成目标，注意这里要用${ALL_SRCS}!!!
#target_link_libraries(pool thread_pool)	# 添加链接库，power是在math子目录的CMakeLists中定义的



