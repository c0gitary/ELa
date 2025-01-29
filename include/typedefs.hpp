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

struct State {
    std::vector<Parameter> params;

    void set_var(const Variable::Type& type, const std::string& name, const std::string& val) {
        this->vars[name] = {
            .type = type,
            .name = name,
            .value = val
        };
    }

    void rem_var(const Variable& var) noexcept {
        if(this->contains(var.name))
            this->vars.erase(var.name);
    }

    void rem_var(const std::string& varName) noexcept {
        if(this->contains(varName))
            this->vars.erase(varName);
    }


    Variable get_var(const std::string& name) noexcept {
        return this->vars[name];
    }

    bool contains(const std::string& name) const noexcept {
        return this->vars.contains(name);
    }

    std::string get_func_new_var() noexcept {
        std::string __str_func = "";
        for(const auto& [nameVar, Var] : this->vars){
            __str_func += ("новая_переменная(" + nameVar + "," + Var.value + ");");
        }
        return __str_func;
    }

private:
    std::unordered_map<std::string, Variable> vars;
};