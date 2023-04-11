cmake_minimum_required(VERSION 3.24)
project(Hashmap)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hashmap HashmapInterface.h Hashmap.h tests.cpp Pair.h)
