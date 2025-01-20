cmake_minimum_required(VERSION 3.18)

project(bigIntLib
        VERSION 1.0.0
        DESCRIPTION "A library for working with big integers written in C++"
        LANGUAGES CXX)

set(CMAKE_C_COMPILER /usr/bin/cc)      
set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_library(BigIntLib SHARED ${SRC_DIR}/bigInt.cpp)

target_include_directories(BigIntLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(BigInt ALIAS BigIntLib)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

add_subdirectory(examples)