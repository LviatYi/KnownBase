cmake_minimum_required(VERSION 3.29)
project(keyLeetCode)

set(CMAKE_CXX_STANDARD 17)

include_directories(LeetCodeKey)

add_executable(LeetCode LeetCodeKey/Main.cpp
        LeetCodeKey/Main.h
        LeetCodeKey/LeetcodeUtil.h
        LeetCodeKey/LeetcodeUtil.cpp
        LeetCodeKey/Solution200.h
        LeetCodeKey/Solution200.cpp
        LeetCodeKey/Solution1702.h
        LeetCodeKey/Solution1702.cpp
        LeetCodeKey/Solution2617.h
        LeetCodeKey/Solution2617.cpp
        LeetCodeKey/Solution22.cpp
        LeetCodeKey/Solution402.cpp
        LeetCodeKey/Solution394.h
        LeetCodeKey/Solution394.cpp
        LeetCodeKey/Solution924.h
        LeetCodeKey/Solution924.cpp
        LeetCodeKey/Solution45.h
        LeetCodeKey/Solution45.cpp
        LeetCodeKey/Solution132.h
        LeetCodeKey/Solution135.h
        LeetCodeKey/Solution135.cpp
        LeetCodeKey/Solution179.cpp
        LeetCodeKey/Solution179.h
        LeetCodeKey/Interval0808.h
        LeetCodeKey/Interval0808.cpp
        LeetCodeKey/Solution84.cpp
        LeetCodeKey/Solution354.cpp
        LeetCodeKey/Solution300.cpp
        LeetCodeKey/Solution554.cpp
        LeetCodeKey/Solution1004.cpp
        LeetCodeKey/Solution1094.cpp
        LeetCodeKey/Solution1450.h
        LeetCodeKey/Solution1450.cpp
        LeetCodeKey/Solution253.cpp
)
