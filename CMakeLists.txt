cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

project(ela)

add_executable(${PROJECT_NAME} src/main.cpp
        include/utils.hpp
        include/typedefs.hpp
        include/operator.hpp
)