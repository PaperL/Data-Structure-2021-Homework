cmake_minimum_required(VERSION 3.16)
project(Data-Structure-2021-Homework)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
include_directories(${PROJECT_SOURCE_DIR}/Homework-4/src/)
set(src_path ${PROJECT_SOURCE_DIR}/Homework-4/src/)

add_executable(code ${src_path}/1130.cpp)