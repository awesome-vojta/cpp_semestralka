cmake_minimum_required(VERSION 3.9)
project(lesson08)

set(CMAKE_CXX_STANDARD 11)

add_executable(lesson08 main.cpp Work.cpp Work.h PrivateWork.cpp PrivateWork.h CompanyWork.cpp CompanyWork.h Worker.cpp Worker.h Stats.cpp Stats.h)