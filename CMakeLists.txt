cmake_minimum_required(VERSION 2.6)

project(cansat)
set(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories(src)

file(GLOB_RECURSE src src/tests/*.cpp)

add_executable(
    tests
    ${src}
    )

target_link_libraries(
    tests
    CppUTest
    CppUTestExt
    )

add_custom_target(check ./tests -c DEPENDS tests)
