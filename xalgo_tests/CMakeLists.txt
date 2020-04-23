cmake_minimum_required(VERSION 3.15)
project(xalgo_tests)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE files "src/*.cpp")

add_executable(xalgo_tests ${files})
target_link_libraries(xalgo_tests PRIVATE xalgo)
