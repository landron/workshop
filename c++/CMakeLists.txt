cmake_minimum_required(VERSION 3.21)

project(workshop)

# Add all CMake subprojects
add_subdirectory(01-cmake/01-start)
add_subdirectory(01-cmake/02-vcpkg)
add_subdirectory(01-cmake/03-vs-llvm)
add_subdirectory(01-cmake/04-vs-llvm-vcpkg)
add_subdirectory(03-test-main)
add_subdirectory(04-test-main-c)
add_subdirectory(102-modern-cpp-challenge)
add_subdirectory(11-tests-collection/cpp17/copy-elision)
