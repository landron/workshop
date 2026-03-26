#[[
    * go to build folder
    * VsDevCmd.bat -arch=amd64
    * cmake -G Ninja <path to this CMakeLists.txt folder>
    * ninja

    find_package(Libevent CONFIG REQUIRED)
    target_link_libraries(main PRIVATE libevent::core libevent::extra)

    Use: C Coding Assessments #test
]]
cmake_minimum_required(VERSION 3.21...3.30)

#   vcpkg integration
# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
    message(STATUS "[04-test-main-c] CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
endif()

# For compilers that have no notion of a C standard level, such as Microsoft Visual C++ before VS 16.7, this property has no effect.
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(time_server C)

find_package(Libevent REQUIRED)

add_executable(${PROJECT_NAME} main.c clock.c)
target_link_libraries(${PROJECT_NAME} PRIVATE libevent::core)
