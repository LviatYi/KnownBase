# CMakeList.txt: CMakeInstance 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

# 顶级 CMakeLists 文件的首行始终应为 cmake_minimum_required。CMake 允许向下兼容
cmake_minimum_required (VERSION 3.8)

# project 指定工程名与支持语言 C|CXX。
# 顶级 CMakeLists 文件的第二行始终应为 project。
project(CMakeInstance) # 默认支持所有语言
# project(CMakeInstance CXX) # 支持 C++
# 该指令隐式定义了 CMAKE 变量：
#   PROJECT_BINARY_DIR = CMakeInstance_BINARY_DIR
#   PROJECT_SOURCE_DIR = CMakeInstance_SOURCE_DIR
#   PROJECT_IS_TOP_LEVEL = CMakeInstance_IS_TOP_LEVEL

# set 设置变量，包括普通变量、缓存变量或环境变量
# 接受 0 或多个参数
set(SRC_LIST CMakeInstance.cpp)
# set(SRC_LIST CMakeInstance.cpp a.cpp b.cpp)
# CMake 定义了许多变量，seealso [https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#manual:cmake-variables(7)]
set(CMAKE_CXX_STANDARD 17)

# message 向日志记录一条消息，一般消息需指定模式与消息，检查报告需指定检查状态与消息
# 常见模式：
#   SEND_ERROR 错误，跳过生成
#   FATAL_ERROR 致命错误，停止处理和生成
#   WARNING 警告，继续处理
#   STATUS 输出一般级消息
#   DEBUG 输出 debug 级消息
#   TRACE 输出 trace 级消息

# 添加子目录到生成，并设置输出目录，否则输出到同目录。
add_subdirectory(src bin)

# add_executable 通过指定源文件生成指定名称的可执行文件
# 允许多种行为：
#   生成可执行文件
#   导入可执行文件
#   创建可执行文件别名
# add_executable (main ${SRC_LIST})

# if (CMAKE_VERSION VERSION_GREATER 3.12)
#   set_property(TARGET CMakeInstance PROPERTY CXX_STANDARD 20)
# endif()
