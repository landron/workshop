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

message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
#message("VCPKG_TARGET_ARCHITECTURE=${VCPKG_TARGET_ARCHITECTURE}")
#message("VCPKG_PLATFORM_TOOLSET=${VCPKG_PLATFORM_TOOLSET}")

project(hello-vcpkg)

#[[
    see https://github.com/Microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md

    vcpkg install sqlite3 --triplet x64-windows
    ]]
find_package(Sqlite3 REQUIRED)

add_executable(${PROJECT_NAME} hello.cpp ../ReadMe.txt)
# it also adds include path
target_link_libraries(${PROJECT_NAME} sqlite3)
