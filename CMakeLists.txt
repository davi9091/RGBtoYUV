cmake_minimum_required(VERSION 3.12)
project(RGBtoYUV)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBtoYUV main.cpp bmp.h bmp.cpp yuv420.h yuv420.cpp)