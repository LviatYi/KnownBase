cmake_minimum_required(VERSION 3.29)
project(keyOd)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")

add_executable(keyOd main.cpp
        Od2518.cpp
        Od2520.cpp
        Od2523.cpp
        Od2532.cpp
        Od2533.cpp
        Od4610.cpp
        Od4500.cpp
        Od4206.cpp
        OdRun1.cpp
        OdRun2.cpp
        OdRun3.cpp
)
