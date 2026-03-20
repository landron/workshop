#[[
    ccmake --build . --clean-first --verbose
]]
cmake_minimum_required(VERSION 3.21...3.30)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()
message(STATUS "[master] VCPKG_ROOT=$ENV{VCPKG_ROOT}")
message(STATUS "[master] CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

# Prefer vcpkg libraries over system
set(VCPKG_PREFER_SYSTEM_LIBS OFF)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

project(workshop)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add all CMake subprojects
add_subdirectory(01-cmake/01-start)
add_subdirectory(01-cmake/02-vcpkg)
add_subdirectory(01-cmake/03-vs-llvm)
add_subdirectory(01-cmake/04-vs-llvm-vcpkg)
add_subdirectory(03-test-main)
add_subdirectory(04-test-main-c)
add_subdirectory(102-modern-cpp-challenge)
add_subdirectory(11-tests-collection/cpp17/copy-elision)
