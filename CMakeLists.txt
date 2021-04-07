cmake_minimum_required(VERSION 3.16)
project(Data-Structure-2021-Homework-2)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)
add_executable(code ${src_dir} src/1100.cpp)