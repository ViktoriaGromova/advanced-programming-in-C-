cmake_minimum_required(VERSION 3.18)
project(BigInteger)

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}../include)

add_library(BigInt SHARED ${SRC_DIR}/bigInt.cpp)

file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
add_executable(bigIntTests ${TEST_SOURCES})
target_link_libraries(bigIntTests PRIVATE ${GTEST_LIBRARIES} pthread BigInt)

enable_testing()
add_test(NAME bigIntTest COMMAND my_tests)