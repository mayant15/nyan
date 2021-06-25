cmake_minimum_required(VERSION 3.13)
project(nyan)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(nyantest tests/doctest.cpp)

set(NYANPERF_SOURCES
    benchmarks/compose.cpp
)
add_executable(nyanperf ${NYANPERF_SOURCES})
