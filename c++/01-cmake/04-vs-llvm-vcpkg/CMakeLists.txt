#[[
    toolset (CMAKE_GENERATOR_TOOLSET): llvm-vs2017, but also builds with VS only
    CMAKE_TOOLCHAIN_FILE : needed for find_package
    ]]
cmake_minimum_required(VERSION 3.21...3.30)

# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}")
    message(STATUS "VCPKG_ROOT=${VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
endif()

project(hello-vs-llvm-vcpkg)

add_executable(${PROJECT_NAME} hello.cpp ../ReadMe.md)

# must be after project declaration
find_package(SQLite3 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SQLite3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARY})

# "C:\WINDOWS\system32\cl : Command line warning D9025: overriding '/W3' with '/W4'"
if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<NOT:$<CONFIG:DEBUG>>:-W4>")
endif()
if(CMAKE_GENERATOR_TOOLSET MATCHES "^llvm")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-error=unused-command-line-argument")
endif()

file(RELATIVE_PATH SUBFOLDER ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE SUBFOLDER="${SUBFOLDER}")
