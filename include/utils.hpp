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

    // static Parameter::Type get_type_number(const std::string& number) {
    //     std::size_t incr = 0ULL;
    //     bool is_float = false;
    //
    //     if(number[incr]) incr++;
    //
    //     for(; incr < number.length(); incr++) {
    //         if(std::isdigit(number[incr]))
    //             continue;
    //
    //         if(number[incr] == '.' && !is_float)
    //             is_float = true;
    //     }
    //
    //     return (is_float ? Parameter::Type::FLOAT : Parameter::Type::INTEGER);
    // }

    static std::string get_type_value(const Parameter::Type& type) {
        switch(type) {
            case Parameter::Type::IDENTIFIER: return "ИДЕНТИФИКАТОР"; break;
            case Parameter::Type::NUMBER: return "ЧИСЛО"; break;
            case Parameter::Type::STRING: return "СТРОКА"; break;
            case Parameter::Type::CONTAINER: return "КОНТЕЙНЕР"; break;
        }
        return "";
    }

    static bool is_number(const std::string& __str) {
        auto it = __str.begin();
        if(*it == '-') ++it;
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

    static bool is_sep(const char& ch) {
        return (defines::sep::is_open(ch) || defines::sep::is_close(ch) || ch == defines::sep::comma);
    }

    static bool is_quote(const char& ch) {
        return ch == defines::sep::quote;
    }

    static bool is_comment(const char& ch) {
        return ch == defines::sep::comment;
    }

    static bool is_container__open(const char& ch) {
        return (ch == defines::sep::open::curly || ch == defines::sep::open::square);
    }

    static bool is_container__close(const char& ch) {
        return (ch == defines::sep::close::curly || ch == defines::sep::close::square);
    }

    static bool is_string(const std::string& __value) {
        return __value.front() == defines::sep::quote && __value.back() == defines::sep::quote;
    }

    static bool is_container(const std::string& __value) {
        return ((__value.front() == defines::sep::open::square && __value.back() == defines::sep::close::square) ||
                (__value.front() == defines::sep::open::curly && __value.back() == defines::sep::close::curly));
    }

    static bool is_bool(const std::string& __value) {
        return (__value == defines::keywords::__true || __value == defines::keywords::__false);
    }

}