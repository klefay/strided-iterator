cmake_minimum_required(VERSION 3.16)

project(strided-iterator)

set(CMAKE_CXX_STANDARD 17)

include(cmake/conan.cmake)

enable_testing()
add_subdirectory(test)
