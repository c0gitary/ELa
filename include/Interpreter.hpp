#pragma once

#include "typedefs.hpp"
#include "defs.hpp"
#include "operator.hpp"
#include "utils.hpp"

#include <functional>
#include <unordered_map>
#include <iostream>

class Interpreter {
    std::unordered_map<std::string, std::function<void(State&)>> functions;
    std::vector<Function> temp_functions;
    State state;

    void __execute_function(const Function& func);
    
public:
    explicit Interpreter(const std::vector<Function>& fn);

    void execute();
};

#include "builtins.hpp"


