#include "../include/Interpreter.hpp"

inline static std::unordered_map<std::string, std::function<void(State&)>> __builtins;

void Interpreter::__execute_function(const Function &func) {
    const auto __it = this->functions.find(func.name);
    if(__it != this->functions.end()) {
        this->state.params = func.params;
        (__it->second)(this->state);
    }
}
    
Interpreter::Interpreter(const std::vector<Function> &fn) {
    this->temp_functions = fn;
    this->functions = builtins::__builtins;
}

void Interpreter::execute() {
    for(const auto& function : this->temp_functions) {
        this->__execute_function(function);
    }
}

