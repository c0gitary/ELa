#pragma once

#include <string>
#include <unordered_map>
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

struct Variable {
    enum class Type {
        INT,
        FLOAT,
        IDENTIFIER,
        STRING,
        BOOL,
        CONTAINER
    } type;
    std::string name;
    std::string value;
};

static std::unordered_map<std::string, Variable> global_variables;

struct State {
    std::vector<Parameter> params;

    void set_var(const Variable::Type& type, const std::string& name, const std::string& val) {
        global_variables[name] = {
            .type = type,
            .name = name,
            .value = val
        };
    }

    void rem_var(const Variable& var) noexcept {
        if(this->contains(var.name))
            global_variables.erase(var.name);
    }

    void rem_var(const std::string& varName) noexcept {
        if(this->contains(varName))
            global_variables.erase(varName);
    }


    Variable get_var(const std::string& name) noexcept {
        return global_variables[name];
    }


    bool contains(const std::string& name) const noexcept {
        return global_variables.contains(name);
    }
};

namespace error::type {
    
    enum class Main {
        INVALID_ARGS,
        INALID_EXT
    };
    
    enum class Parser {
        EXPECTED_CHAR,
        EXPECTED_ID,
        UNKNOWN_TYPE
    };

    // enum class Runtime {};
};