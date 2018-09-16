cmake_minimum_required(VERSION 3.0)
project(hash-code-aco)
file(GLOB_RECURSE sources src/*.cpp src/*.h)
add_executable(hash-code-aco ${sources})

# One might think that the following would speed things up, but on
# my machine (i7-4702MQ, g++ 8.2.0 on debian stretch, Linux 4.9.11)
# it in fact slows execution down measurably in all cases.
# No idea why.

# include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
# if(COMPILER_SUPPORTS_MARCH_NATIVE)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
# endif()

target_compile_options(hash-code-aco PUBLIC -std=c++17 -Wall -O3)
#target_compile_options(hash-code-aco PUBLIC -std=c++17 -Wall -pg)
target_link_libraries(hash-code-aco PUBLIC pthread)
# Use the following for profiling:
#target_link_libraries(hash-code-aco PUBLIC -pg)
target_include_directories(hash-code-aco PUBLIC src)
