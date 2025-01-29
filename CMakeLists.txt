cmake_minimum_required(VERSION 3.20)

project(ela)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS)

set(INCLUDE_FILES
        include/tools/utils.hpp
        include/tools/typedefs.hpp
        include/tools/operator.hpp
        include/tools/defs.hpp
        include/tools/builtins.hpp
        include/Parser.hpp
        include/Lexer.hpp
        include/Interpreter.hpp
        include/Error.hpp
)

set(SRC_FILES
        src/main.cpp
        src/Lexer.cpp
        src/Parser.cpp
        src/Interpreter.cpp
        src/Error.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SRC_FILES})
