cmake_minimum_required(VERSION 3.17)
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER_WORKS 1)
project(sk)

set(CMAKE_CXX_STANDARD 14)

add_executable(sk main.cpp communication.cpp communication.h user.cpp user.h server.cpp server.h channel.cpp channel.h)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")