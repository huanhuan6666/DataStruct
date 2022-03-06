cmake_minimum_required(VERSION 3.21)
project(data_struct)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_struct main.cpp LinearList/LinearList.h LinearList/SeqList.h LinearList/LinkList.h)
