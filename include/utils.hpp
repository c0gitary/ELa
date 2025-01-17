#pragma once

#include "typedefs.hpp"


namespace utils{

    static std::string ctos(const char __ch) {
        return std::basic_string<char>(__ch, 1);
    }

    static Variable::Type get_type_number(const std::string& number) {
        std::size_t incr = 0ULL;
        bool is_float = false;

        if(number[incr]) incr++;

        for(; incr < number.length(); incr++) {
            if(std::isdigit(number[incr]))
                continue;

            if(number[incr] == '.' && !is_float)
                is_float = true;
        }

        return (is_float ? Variable::Type::FLOAT : Variable::Type::INTEGER);
    }

    static bool is_number(const std::string& __str) {
        auto it = __str.begin();
        for(;it != __str.end() && std::isdigit(*it) || *it=='.'; ++it) {}
        return !__str.empty() && it == __str.end();
    }

    static std::string file__read_and_write(const std::string& __filename){
        std::ifstream file(__filename);

        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
        
         
    }

}