#pragma once

#include <string>
#include <vector>

struct Parameter {
    enum class Type {
        IDENTIFIER,
        STRING,
        NUMBER,
        CONTAINER
    } type;

    std::string name;
};

struct Function {
    std::string name;
    std::vector<Parameter> params;
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