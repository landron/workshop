#[[
    https://stackoverflow.com/questions/38171878/how-do-i-tell-cmake-to-use-clang-on-windows
    https://github.com/arves100/llvm-vs2017-integration
        (see ReadMe.txt)

    clang-cl : warning : argument unused during compilation: '/Gm-' [-Wunused-command-line-argument]

    toolset (CMAKE_GENERATOR_TOOLSET): llvm-vs2017, but also builds with VS only
    ]]
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
endif()

#   https://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script 
if(0)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()

project(hello-vs-llvm)

add_executable(${PROJECT_NAME} hello.cpp ../ReadMe.txt)
# "C:\WINDOWS\system32\cl : Command line warning D9025: overriding '/W3' with '/W4'"
if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<NOT:$<CONFIG:DEBUG>>:-W4>")
endif()
if(CMAKE_GENERATOR_TOOLSET MATCHES "^llvm")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-error=unused-command-line-argument")
endif()

