cmake_minimum_required(VERSION 3.0)

project("Zadanie1")

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)