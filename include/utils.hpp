#pragma once

#include <fstream>
#include <sstream>

#include "typedefs.hpp"
#include "defs.hpp"

namespace utils{

    static std::string ctos(const char& __ch) {
        std::string __t;
        __t += __ch;
        return __t;
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

    static std::string file_to_str(const std::string& __filename) {
        std::ifstream __file(__filename);
        if(!__file.is_open()) throw std::runtime_error("File not opening");

        std::stringstream __buffer;
        __buffer << __file.rdbuf();

        return __buffer.str();
    }

}