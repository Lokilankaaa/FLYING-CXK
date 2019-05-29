cmake_minimum_required(VERSION 3.13)
project(c_big_work)

set(CMAKE_C_STANDARD 99)
include_directories(inc)
aux_source_directory(src DIR_SRCS)


link_directories(lib)


add_executable(${PROJECT_NAME} ${DIR_SRCS} main.c)

target_link_libraries(${PROJECT_NAME} WinMM)