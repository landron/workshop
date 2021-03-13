#[[
	* go to build folder
	* VsDevCmd.bat -arch=amd64
	* cmake -G Ninja <path to this CMakeLists.txt folder>
	* ninja

	find_package(Libevent CONFIG REQUIRED)
    target_link_libraries(main PRIVATE libevent::core libevent::extra)
]]

cmake_minimum_required(VERSION 3.12)

#	vcpkg integration
# https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}")
    message(STATUS "VCPKG_ROOT=${VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()
#message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")


#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(time_server C)

find_package(Libevent REQUIRED)

add_executable(${PROJECT_NAME} main.c clock.c)
target_link_libraries(${PROJECT_NAME} PRIVATE libevent::core)
