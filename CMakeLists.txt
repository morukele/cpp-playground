cmake_minimum_required(VERSION 4.1)  # CMake version check
project(cpp_playground) # Create project "cpp_playground"

set(CMAKE_CXX_STANDARD 20)            # Enable C++20 standard
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fconcepts-ts") # setting up c++ 20 features

# Fetch Google Benchmark
#include(FetchContent)

# Google benchmark requires GoogleTest for some configurations
#set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
#set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
#set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "" FORCE)

#FetchContent_Declare(
#        benchmark
#        GIT_REPOSITORY https://github.com/google/benchmark.git
#        GIT_TAG v1.9.4
#)

# FetchContent_MakeAvailable(benchmark)

find_package(sycl)

# Define the benchmark executable
add_executable(cpp_playground main.cpp)

# Include headers
target_include_directories(cpp_playground PRIVATE include, sycl)

# Link Google Benchmark
#target_link_libraries(cpp_playground
#        PRIVATE
#        benchmark::benchmark
#        benchmark::benchmark_main
#)