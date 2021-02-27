cmake_minimum_required(VERSION 3.16)
project(Data-Structure-2021-Homework-1)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# -Wall 显示所有编译信息 -g 支持调试模式,关闭所有优化
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)
set(src_dir
        # ${PROJECT_SOURCE_DIR}/src/1083.cpp
        # ${PROJECT_SOURCE_DIR}/src/1088.cpp
        # ${PROJECT_SOURCE_DIR}/src/1089.cpp
        # ${PROJECT_SOURCE_DIR}/src/1095.cpp
        # ${PROJECT_SOURCE_DIR}/src/main.cpp
        # ${PROJECT_SOURCE_DIR}/src/test.cpp
        # 等效于将本内容逐个列于 add_executable 中
)
add_executable(code ${src_dir} src/1088.cpp)