#[[
	* go to build folder
	* (Windows) VsDevCmd.bat -arch=amd64
	* cmake -G Ninja <path to this CMakeLists.txt folder>
	* ninja

	with build folder outside this repository, you can do:
		cmake -G Ninja ../workshop/c++/03-test-main/

	Use: C++ Coding Assessments #test
]]

# The first number (3.21) is your floor. It says: "This project requires at least CMake 3.21 to compile."
# "If the user has a version as new as 3.30, please use the modern, updated logic for that version."
cmake_minimum_required(VERSION 3.21...3.30)

# C++20 was a "Major" release (like C++11). It fundamentally changed how we write C++ architecture. 
# C++23, by comparison, is a "Minor" refinement
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(simple-test)

add_executable(${PROJECT_NAME} test.cpp)

# Enable common warnings - vital for troubleshooting performance/bugs
if(MSVC)
    target_compile_options(simple-test PRIVATE /W4 /WX)
else()
    target_compile_options(simple-test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
