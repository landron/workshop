#[[
    vcpkg install gtest --triplet x64-windows

    "The package gtest is compatible with built-in CMake targets:
        enable_testing()
        find_package(GTest MODULE REQUIRED)
        target_link_libraries(main PRIVATE GTest::GTest GTest::Main)
        add_test(AllTestsInMain main)
    "

    \todo :
        * multiple configurations with VS Community 2017, 15.9.x
            (meaning? using clang ?)
        * clang-format

    Knowledge base
        * fast command line build with Ninja:
            see https://github.com/landron/workshop/tree/master/c%2B%2B/01-cmake,
                    4.Windows, Visual Studio 15 2017, Ninja
        * CMake GUI: "Delete cache" after defining VCPKG_ROOT
            (set DOS command)
        * update vcpkg: git pull, bootstrap-vcpkg.bat
        * update packages: see vcpkg parameters
    ]]
cmake_minimum_required(VERSION 3.12)

# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}")
    message(STATUS "VCPKG_ROOT=${VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(modern-cpp-challenge)

find_package(GTest MODULE REQUIRED)

add_executable(${PROJECT_NAME} main.cpp problems.h p01.cpp p0203.cpp)
# it also adds include path
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)