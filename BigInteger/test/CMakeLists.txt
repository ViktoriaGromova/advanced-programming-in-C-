project(BigInteger)

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)

file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
add_executable(bigIntTests ${TEST_SOURCES})
target_link_libraries(bigIntTests PRIVATE ${GTEST_LIBRARIES} pthread BigInt)

add_test(NAME bigIntTest COMMAND my_tests)