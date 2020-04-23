cmake_minimum_required(VERSION 3.15)
project(xalgo)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE files "src/*.cpp")

add_library(xalgo STATIC ${files})

target_include_directories(xalgo PUBLIC include)
