#pragma once

#include <fstream>
#include <sstream>
#include <cstdint>
#include <algorithm>

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

    static bool is_float(const std::string& __num) {
        const auto cnt_dot = std::ranges::count(__num, '.');
        if(is_number(__num) && cnt_dot == 1) return true;
        if(cnt_dot == 0) return false;
        throw std::runtime_error("Error number");
    }

    template<typename T>
    static T convert_number(const Variable& __var) {
        if(__var.type == Variable::Type::INT)
            return std::stoi(__var.value);
        if(__var.type == Variable::Type::FLOAT)
            return std::stof(__var.value);
        throw std::runtime_error("CONVERT_NUMBER -> Invalid args");
    }



    static std::string file_to_str(const std::string& __filename) {
        std::ifstream __file(__filename);
        if(!__file.is_open()) throw std::runtime_error("File not opening");

        std::stringstream __buffer;
        __buffer << __file.rdbuf();

        return __buffer.str();
    }

    static Variable::Type get_type_param(const Parameter& param) {
        switch(param.type) {
            case Parameter::Type::NUMBER: return (is_float(param.name) ? Variable::Type::FLOAT : Variable::Type::INT);
            case Parameter::Type::STRING: return Variable::Type::STRING;
            case Parameter::Type::CONTAINER: return Variable::Type::CONTAINER;
            case Parameter::Type::IDENTIFIER: return Variable::Type::IDENTIFIER;
        }
        throw std::runtime_error("Invalid type");
    }

    static Variable set_anon_number(const std::string& number) {
        static unsigned __number_idx__{};
        const auto var = Variable(
            (is_float(number) ? Variable::Type::FLOAT : Variable::Type::INT),
            defines::__internal::anon_number + __number_idx__ + number,
            number
        );
        __number_idx__++;
        return var;
    }

    static bool is_anon_number(const Variable& var) {
        return var.name.find(defines::__internal::anon_number) != std::string::npos;
    }

    static bool is_id_param(const Parameter& param) {
        return param.type == Parameter::Type::IDENTIFIER;
    }

    static bool is_number_param(const Parameter& param) {
        return param.type == Parameter::Type::NUMBER;
    }

    static bool is_string_param(const Parameter& param) {
        return param.type == Parameter::Type::STRING;
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
        return ch == defines::sep::open::curly;
    }

    static bool is_container__close(const char& ch) {
        return ch == defines::sep::close::curly;
    }

    static bool is_string(const std::string& __value) {
        return __value.front() == defines::sep::quote && __value.back() == defines::sep::quote;
    }

    static bool is_container(const std::string& __value) {
        return (__value.front() == defines::sep::open::curly && __value.back() == defines::sep::close::curly);
    }

    static bool is_bool(const std::string& __value) {
        return (__value == defines::keywords::logic::__true || __value == defines::keywords::logic::__false);
    }

    static std::string extract_content(const std::string& __str) {
        if(__str.size() < 2 || __str.front() != defines::sep::quote || __str.back() != defines::sep::quote)
            return __str;
        return __str.substr(1ULL, __str.size() - 2ULL);
    }

    static std::string unpack(const std::string& __container) {
        if(is_container(__container)) 
            return __container.substr(1ULL, __container.size() - 2ULL);
        throw std::runtime_error("ERROR: Unpack container");
    }

    static std::string add_quotes(const std::string& __str) {
        return defines::sep::quote + __str + defines::sep::quote;
    }
}