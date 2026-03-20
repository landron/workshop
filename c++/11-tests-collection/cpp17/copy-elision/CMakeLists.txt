#[[
    cmake -G Ninja ../../workshop/c++/11-tests-collection/cpp17/copy-elision/
]]
#[[
    vcpkg install gtest
        vcpkg install gtest --triplet x64-windows

    "The package gtest is compatible with built-in CMake targets:
        enable_testing()
        find_package(GTest MODULE REQUIRED)
        target_link_libraries(main PRIVATE GTest::GTest GTest::Main)
        add_test(AllTestsInMain main)
    "

    copy elision help:
        see NonMoveable.h

    \todo : multiple configurations with VS Community 2017, 15.9.4
        Best is command line & ninja: https://github.com/landron/workshop/tree/master/c%2B%2B/01-cmake

    Knowledge base
        * CMake GUI: "Delete cache" after defining VCPKG_ROOT
    ]]
# The first number (3.21) is your floor. It says: "This project requires at least CMake 3.21 to compile."
# "If the user has a version as new as 3.30, please use the modern, updated logic for that version."
cmake_minimum_required(VERSION 3.21...3.30)

# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}")
    message(STATUS "VCPKG_ROOT=${VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

set(CMAKE_CXX_STANDARD 23) 
# set(CMAKE_CXX_STANDARD 14) # try 14 for this test
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(copy-elision)

find_package(GTest MODULE REQUIRED)

add_executable(${PROJECT_NAME} main.cpp NonMoveable.h)
# it also adds include path
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)
