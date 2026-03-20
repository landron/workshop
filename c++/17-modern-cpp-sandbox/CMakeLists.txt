#[[
    cmake -G Ninja ../../workshop/c++/17-modern-cpp-sandbox/
]]

# The first number (3.21) is your floor. It says: "This project requires at least CMake 3.21 to compile."
# "If the user has a version as new as 3.30, please use the modern, updated logic for that version."
cmake_minimum_required(VERSION 3.21...3.30)

# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

project(modern-cpp-sandbox)
add_executable(${PROJECT_NAME} main.cpp 01_std_span.h 02_alignment.h 03_polymorphism.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

find_package(GTest MODULE REQUIRED)
# it also adds include path
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)
