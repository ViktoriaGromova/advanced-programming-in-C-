file(GLOB EXAMPLES "*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}../include)

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries()
endforeach()



target_link_libraries(mylib-tests
    PRIVATE
        mylib::mylib
        gtest_main)
