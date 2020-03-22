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

     Without user-wide integration ("vcpkg integrate install"), full paths are needed:
     	SQLite3_INCLUDE_DIR, SQLite3_LIBRARY (instead of saying just sqlite3)
    ]]
find_package(sqlite3 REQUIRED)

add_executable(${PROJECT_NAME} hello.cpp ../ReadMe.md)
target_include_directories(${PROJECT_NAME} PRIVATE ${SQLite3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARY})
