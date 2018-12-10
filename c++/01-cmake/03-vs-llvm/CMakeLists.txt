#[[
    https://stackoverflow.com/questions/38171878/how-do-i-tell-cmake-to-use-clang-on-windows
    https://github.com/arves100/llvm-vs2017-integration
        (see ReadMe.txt)

    clang-cl : warning : argument unused during compilation: '/Gm-' [-Wunused-command-line-argument]
    ]]
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

project(hello-vs-llvm)

add_executable(${PROJECT_NAME} hello.cpp ../ReadMe.txt)
target_compile_options(${PROJECT_NAME} PRIVATE "-W4" "-Wno-error=unused-command-line-argument")

