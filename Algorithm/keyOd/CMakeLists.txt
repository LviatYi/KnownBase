cmake_minimum_required(VERSION 3.29)
project(keyOd)

set(CMAKE_CXX_STANDARD 17)

add_executable(keyOd main.cpp
        Od2518.cpp
        Od2520.cpp
        Od2523.cpp
        Od2532.cpp
        Od2533.cpp
)
