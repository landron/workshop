#[[
    cmake -G Ninja ../../mine/workshop/c++/11-tests-collection
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

project(copy-elision)
add_executable(${PROJECT_NAME} cpp17/copy-elision/main.cpp)

# CTest to test C++ compilation guards
enable_testing()

set_target_properties(${PROJECT_NAME} PROPERTIES
    # CXX_STANDARD 14 # try 14 for this test
    CXX_STANDARD 26
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

get_target_property(TARGET_STD ${PROJECT_NAME} CXX_STANDARD)
# message(STATUS "TARGET_STD=${TARGET_STD}")
if(TARGET_STD EQUAL 14)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-fno-elide-constructors>
        $<$<CXX_COMPILER_ID:Clang>:-fno-elide-constructors>
    )
    target_compile_definitions(${PROJECT_NAME} PRIVATE TEST_CPP_14=1)
else() 
    # it forces C++17
    find_package(GTest MODULE REQUIRED)
    # it also adds include path
    target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)
endif()

add_test(
    # nrvo = Named Return Value Optimization
    NAME nrvo_should_fail
    COMMAND ${CMAKE_CXX_COMPILER}
            ${CMAKE_CURRENT_SOURCE_DIR}/cpp17/copy-elision/nrvo_fails.cpp
            -c
)
# set_tests_properties(nrvo_should_fail PROPERTIES WILL_FAIL TRUE)
# The test passes ONLY if it fails due to the deleted move constructor
set_tests_properties(nrvo_should_fail PROPERTIES 
    PASS_REGULAR_EXPRESSION "attempting to reference a deleted function|use of deleted function"
)
