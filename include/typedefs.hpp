#pragma once

#include <string>
#include <vector>

struct Variable {
    enum class Type {
        INTEGER,
        FLOAT,
        BOOLEAN,
        STRING,
        CONTAINER
    } type;

    std::string name;
    std::string value;
};

struct Token {
    enum class Type {
        IDENTIFIER,
        NUMBER,
        STRING,
        CONTAINER,
        SEMICOLON,
        SEPARATOR,
        END
    } type;

    std::string name;
};