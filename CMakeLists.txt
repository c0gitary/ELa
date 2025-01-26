cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS)

project(ela)

add_executable(${PROJECT_NAME} 
        main.cpp
        include/utils.hpp
        include/typedefs.hpp
        include/operator.hpp
        src/Lexer.cpp
        include/Lexer.hpp
        include/defs.hpp
        include/defs.hpp
        src/Parser.cpp
        include/Parser.hpp
        include/builtins.hpp
        src/Interpreter.cpp
        include/Interpreter.hpp
)