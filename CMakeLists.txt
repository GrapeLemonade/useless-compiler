cmake_minimum_required(VERSION 3.17)
project(E4)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)
add_compile_definitions(LOCAL_DEBUG)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,268435456")

add_executable(main main.cpp)

