cmake_minimum_required(VERSION 3.13)
project(nyan)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES tests/main.cpp)
add_executable(nyantest ${SOURCES})
target_include_directories(nyantest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
