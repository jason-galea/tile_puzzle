CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(tile_puzzle)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(exec_name tile_puzzle)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

file(GLOB classes_dir "classes/*.h" "classes/*.cpp")
set(sources main.cpp ${classes_dir})

add_executable(${exec_name} ${sources})

