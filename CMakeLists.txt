cmake_minimum_required(VERSION 3.0)
project(hash-code-aco)
file(GLOB_RECURSE sources src/*.cpp src/*.h)
add_executable(hash-code-aco ${sources})
target_compile_options(hash-code-aco PUBLIC -std=c++17 -Wall -g)
#target_link_libraries(hash-code-aco PUBLIC m)
# Use the following for profiling:
#target_link_libraries(hash-code-aco PUBLIC -pg)
target_include_directories(hash-code-aco PUBLIC src)
