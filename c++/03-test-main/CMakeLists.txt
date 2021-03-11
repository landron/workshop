#[[
	* go to build folder
	* VsDevCmd.bat -arch=amd64
	* cmake -G Ninja <path to this CMakeLists.txt folder>
	* ninja
]]
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(simple-test)

add_executable(${PROJECT_NAME} test.cpp)