cmake_minimum_required(VERSION 3.21)
project(task_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(task_5
        Circle.hpp
        Point.hpp
        q5.cpp
        Rectangle.hpp
        Shape.hpp
        Size.hpp)
