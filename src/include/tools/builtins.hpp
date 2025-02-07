#pragma once

#include "../Lexer.hpp"
#include "../Parser.hpp"
#include "../Interpreter.hpp"

#include <iostream>
#include <functional>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <filesystem>

namespace builtins {

    namespace internal {
        static void new_var(State&);
        static void remove_var(State&);
    }

    namespace io {
        static void print(State&);
        static void input(State&);
        static void clear(State&);
        static void pause(State&);
        static void new_line(State&);
    }

    namespace file {
        static void create(State&);
        static void open(State&);
        static void close(State&);
        static void remove(State&);
        static void read(State&);
        static void write(State&);
        static void add(State&);
        static void move(State&);
        static void copy(State&);
    }

    namespace folder {
        static void newfolder(State&);
        static void remfolder(State&);
        static void movefolder(State&);
    }


    namespace time {
        static void current_date(State&);
        static void current_time(State&);
    }

    namespace math {
        static void mul(State&);
        static void div(State&);
        static void sum(State&);
        static void sub(State&);
        static void mod(State&);
        static void log(State&);
        static void pow(State&);
        static void rand(State&);
        static void round(State&);
        static void floor(State&);
        static void ceil(State&);
        static void abs(State&);
        static void l_and(State&);
        static void l_or(State&);
        static void factorial(State&);

        template<class T, class U, template <class> class Op>
        static void binary_op(State&);

        template<class T, template <class> class Op>
        static void math_func_one_arg(State&);

        template<template <class> class Op>
        static void math_func(State&);

    }

    namespace container {}

    namespace string {
            static void concat(State&);
            static void substring(State&);
            static void lenght(State&);
        }

    namespace flow {
        static void loop(State&);
        static void repeat(State&);
    }

    inline static std::unordered_map<std::string, std::function<void(State&)>> __builtins {
        {defines::builtins::internal::new_var,   internal::new_var},
        {defines::builtins::internal::rem_var,   internal::remove_var},

        {defines::builtins::io::clear, io::clear},
        {defines::builtins::io::input, io::input},
        {defines::builtins::io::output, io::print},
        {defines::builtins::io::pause, io::pause},
        {defines::builtins::io::new_line, io::new_line},

        {defines::builtins::string::add, string::concat},
        {defines::builtins::string::lenght, string::lenght},
        {defines::builtins::string::substring, string::substring},

        {defines::builtins::time::cur_date, time::current_date},
        {defines::builtins::time::cur_time, time::current_time},

        {defines::builtins::file::create, file::create},
        {defines::builtins::file::open, file::open},
        {defines::builtins::file::read, file::read},
        {defines::builtins::file::write, file::write},
        {defines::builtins::file::add, file::add},
        {defines::builtins::file::move, file::move},
        {defines::builtins::file::copy, file::copy},
        {defines::builtins::file::remove, file::remove},

        {defines::builtins::folder::newfolder, folder::newfolder},
        {defines::builtins::folder::remfolder, folder::remfolder},

        {defines::builtins::math::mul, math::mul},
        {defines::builtins::math::div, math::div},
        {defines::builtins::math::sum, math::sum},
        {defines::builtins::math::sub, math::sub},
        {defines::builtins::math::pow, math::pow},
        {defines::builtins::math::log, math::log},
        {defines::builtins::math::rand, math::rand},
        {defines::builtins::math::round, math::round},
        {defines::builtins::math::l_and, math::l_and},
        {defines::builtins::math::l_or, math::l_or},
        {defines::builtins::math::fact, math::factorial},

        {defines::builtins::flow::loop, flow::loop},
        {defines::builtins::flow::repeat, flow::repeat}
    };

}

inline void builtins::flow::loop(State& s){
    if(s.params.size() == 5 && utils::is_container(s.params[4].name) && utils::is_id_param(s.params[0])){
        const int start = (utils::is_id_param(s.params[1]) ? std::stoi(s.get_var(s.params[0].name).value) : std::stoi(s.params[1].name));
        const int end   = (utils::is_id_param(s.params[2]) ? std::stoi(s.get_var(s.params[1].name).value) : std::stoi(s.params[2].name));
        const int step  = (utils::is_id_param(s.params[3]) ? std::stoi(s.get_var(s.params[2].name).value) : std::stoi(s.params[3].name));

        Lexer __loopLexer(utils::unpack(s.params[4].name));
        __loopLexer.tokenize();
        Parser __loopParser(__loopLexer.get_tokens());
        Interpreter __loopInterpreter(__loopParser.get_functions());

        for(int i = start; i < end; i += step){
            s.set_var(
                Variable::Type::INT,
                s.params[0].name,
                std::to_string(i)
            );
            __loopInterpreter.execute();
        }
        s.rem_var(s.get_var(s.params[0].name));
        return;
    }
    throw std::runtime_error("FLOW::LOOP -> Invalid args");
}

inline void builtins::flow::repeat(State& s){
    if(s.params.size() == 2 && utils::is_container(s.params[1].name)){
        const int count = (utils::is_id_param(s.params[0]) ? std::stoi(s.get_var(s.params[0].name).value) : std::stoi(s.params[0].name));
        if(count < 0)
            throw std::runtime_error("FLOW::REPEAT -> Negative count");

        Lexer __repeatLexer(utils::unpack(s.params[1].name));
        __repeatLexer.tokenize();
        Parser __repeatParser(__repeatLexer.get_tokens());
        Interpreter __repeatInterpreter(__repeatParser.get_functions());
        
        for(unsigned i = 0; i < count; ++i)
            __repeatInterpreter.execute();
        return;
    }
    throw std::runtime_error("FLOW::REPEAT -> Invalid args");
}

inline void builtins::internal::new_var(State & s) {
    if(s.params.size() == 2) {
        const auto ty_var = utils::get_type_param(s.params[1]);
        if(ty_var != Variable::Type::IDENTIFIER)
            s.set_var(ty_var, s.params[0].name, s.params[1].name);
        else {
            if(s.contains(s.params[1].name)) {
                s.set_var(
                    s.get_var(s.params[1].name).type,
                    s.params[0].name,
                    s.get_var(s.params[1].name).value
                );
            }
            else {
                s.set_var(
                    Variable::Type::INT,
                    s.params[0].name,
                    "0"
                );
            }
        }
        return;
    }
    throw std::runtime_error("INTERNAL::NEW_VAR -> Invalid args");
}

inline void builtins::internal::remove_var(State& s) { 
    for(std::size_t i = 0;i < s.params.size(); i++){
        if(utils::is_id_param(s.params[i])){
            s.rem_var(s.params[i].name);
        }
    }
}

inline void builtins::io::print(State & s) {
    for(std::size_t i{}; i < s.params.size(); i++) {
        std::cout << (utils::is_id_param(s.params[i]) ? s.get_var(s.params[i].name).value : utils::extract_content(s.params[i].name)) << ' ';
    }
}

inline void builtins::io::new_line(State&) {
    std::cout << std::endl;
}

inline void builtins::io::input(State &s) {
    if(s.params.size() == 1 && utils::is_id_param(s.params[0])) {
        std::string __input;
        std::getline(std::cin, __input);
        s.set_var(Variable::Type::STRING, s.params[0].name, __input);
        return;
    }
    throw std::invalid_argument("IO::INPUT -> Count params != 2");
}

inline void builtins::io::pause(State &) {
    system("pause");
}

inline void builtins::io::clear(State &) {
    system("cls");
}

inline void builtins::folder::newfolder(State &s) {
    if(s.params.size() == 1){
        const std::string __folderName = utils::extract_content(utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value : s.params[0].name);
        std::filesystem::create_directory(__folderName.c_str());
    }
}

inline void builtins::folder::remfolder(State &s) {
    if(s.params.size() == 1){
        const std::string __folderName = utils::extract_content(utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value : s.params[0].name);
        std::filesystem::remove_all(__folderName.c_str());
    }
}

inline void builtins::file::create(State &s) {
    if(s.params.size() == 1){
        std::ofstream(utils::extract_content((utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value : s.params[0].name)));
    }
}

inline void builtins::file::read(State &s) {
    if(s.params.size() == 2 && utils::is_id_param(s.params[0])) {
        const std::string fileName = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name).value : s.params[1].name);
        if(std::ifstream file(utils::extract_content(fileName)); file.is_open()) {
            std::string str;
            while(std::getline(file, str)){}
            s.set_var(Variable::Type::STRING, s.params[0].name, str);
            file.close();
            return;
        }
        throw std::runtime_error("FILE::READ -> File not opening");
    }
    throw std::runtime_error("FILE::READ -> Invalid args");
}

inline void builtins::file::write(State &s) {
    if(s.params.size() == 2){
        const std::string content = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name).value : s.params[1].name);
        const std::string nameFile = (utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value :  s.params[0].name);
        std::ofstream file(utils::extract_content(nameFile));
        file << utils::extract_content(content);
        file.close();
        return;
    }
    throw std::invalid_argument("FILE::WRITE -> Invalid args");
}

inline void builtins::file::add(State &s) {
    if(s.params.size() == 2){
        const std::string content = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name).value : s.params[1].name);
        const std::string nameFile = (utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value :  s.params[0].name);
        std::ofstream file(utils::extract_content(nameFile), std::ios::app);
        file << utils::extract_content(content);
        file.close();
        return;
    }
    throw std::invalid_argument("FILE::ADD -> Invalid args");
}

inline void builtins::file::remove(State &s) {
    for(std::size_t i = 0; i < s.params.size(); i++){
        std::filesystem::remove(utils::extract_content((utils::is_id_param(s.params[i]) ? s.get_var(s.params[i].name).value : s.params[i].name)));
    }
}

inline void builtins::file::move(State &s) {
    if(s.params.size() == 2){
        const std::string filePath1 = (utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value :  s.params[0].name);
        const std::string filePath2 = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name).value : s.params[1].name);
        std::filesystem::rename(utils::extract_content(filePath1), utils::extract_content(filePath2));
    }
}

inline void builtins::file::copy(State &s) {
    if(s.params.size() == 2){
        const std::string filePath1 = (utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value :  s.params[0].name);
        const std::string filePath2 = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name).value : s.params[1].name);
        std::filesystem::copy(filePath1, filePath2);
    }
}

inline void builtins::file::open(State &s) {
    if(s.params.size() == 1) {
        const auto path = (utils::is_id_param(s.params[0]) ? s.get_var(s.params[0].name).value : s.params[0].name);
        system(std::string(path).c_str());
    }
}

inline void builtins::string::concat(State &s) {
    if(s.params.size() == 3 && utils::is_id_param(s.params[0])) {
        if(s.contains(s.params[1].name) && s.contains(s.params[2].name)) {
            s.set_var(
                Variable::Type::STRING,
                s.params[0].name,
                utils::add_quotes(
                    utils::extract_content(s.get_var(s.params[1].name).value) + utils::extract_content(s.get_var(s.params[2].name).value)
                )
            );
            return;
        }
        throw std::runtime_error("STRING::CONCAT -> ID is not defined");
    }
    throw std::runtime_error("STRING::CONCAT -> Error");
}

inline void builtins::string::lenght(State &s) {
    if(s.params.size() == 2 && utils::is_id_param(s.params[0])) {
        const std::string val = (s.contains(s.params[1].name) ? s.get_var(s.params[1].name).value : s.params[1].name);
        s.set_var(
            Variable::Type::INT,
            s.params[0].name,
            std::to_string(utils::extract_content(val).length() / 2ULL) // TODO temp solve !!!
        );
        return;
    }

    throw std::runtime_error("STRING::LENGHT -> Error");
}

// подстрока(рез, строка, нач_поз_строки, длина_подстроки);
inline void builtins::string::substring(State &s) {
    if (s.params.size() == 4 && utils::is_id_param(s.params[0])) {

        if (s.contains(s.params[1].name) && s.get_var(s.params[1].name).type == Variable::Type::STRING) {
            const std::string value = s.get_var(s.params[1].name).value;
            const std::string content = utils::extract_content(value);

            if (s.contains(s.params[2].name) && s.get_var(s.params[2].name).type == Variable::Type::INT) {
                const int start_pos = std::stoi(s.get_var(s.params[2].name).value);

                if (s.contains(s.params[3].name) && s.get_var(s.params[3].name).type == Variable::Type::INT) {
                    const int length = std::stoi(s.get_var(s.params[3].name).value);

                    if (start_pos >= 0 && start_pos < content.length() && length >= 0 && start_pos + length <= content.length()) {
                        const std::string substring = content.substr(start_pos, length);
                        s.set_var(
                            Variable::Type::STRING,
                            s.params[0].name,
                            utils::add_quotes(substring)
                        );
                    } else {
                        throw std::runtime_error("STRING::SUBSTRING -> Invalid start position or length");
                    }
                } else {
                    throw std::runtime_error("STRING::SUBSTRING -> Length parameter is not an integer");
                }
            } else {
                throw std::runtime_error("STRING::SUBSTRING -> Start position parameter is not an integer");
            }
        } else {
            throw std::runtime_error("STRING::SUBSTRING -> Variable not found or not a string");
        }
        return;
    }

    throw std::runtime_error("STRING::SUBSTRING -> Invalid arguments");
}

inline void builtins::time::current_date(State &s) {
    if(s.params.size() == 1 && utils::is_id_param(s.params[0])) {
        const std::time_t __now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const std::tm* __now_tm = std::localtime(&__now_time);

        std::ostringstream oss;
        oss << std::put_time(__now_tm, "%Y-%m-%d");

        s.set_var(
            Variable::Type::STRING,
            s.params[0].name,
            utils::add_quotes(oss.str())
        );
        return;
    }
    throw std::runtime_error("TIME::CUR_DATE -> Invalid args");
}

inline void builtins::time::current_time(State &s) {
    if(s.params.size() == 1 && utils::is_id_param(s.params[0])) {
        const std::time_t __now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const std::tm* __now_tm = std::localtime(&__now_time);

        std::ostringstream oss;
        oss << std::put_time(__now_tm, "%H:%M:%S");

        s.set_var(
            Variable::Type::STRING,
            s.params[0].name,
            utils::add_quotes(oss.str())
        );
        return;
    }
    throw std::runtime_error("TIME::CUR_TIME -> Invalid args");
}

inline void builtins::math::mul(State &s) {
    builtins::math::binary_op<int, float, std::multiplies>(s);
}

inline void builtins::math::div(State &s) {
    builtins::math::binary_op<int, float, std::divides>(s);
}

inline void builtins::math::sum(State &s) {
    builtins::math::binary_op<int, float, std::plus>(s);
}

inline void builtins::math::sub(State &s) {
    builtins::math::binary_op<int, float, std::minus>(s);
}

inline void builtins::math::mod(State &s) {
    builtins::math::binary_op<int, int, std::modulus>(s);
}

inline void builtins::math::l_and(State &s) {
    builtins::math::binary_op<int, int, std::logical_and>(s);
}

inline void builtins::math::l_or(State &s) {
    builtins::math::binary_op<int, int, std::logical_or>(s);
}

inline void builtins::math::log(State &s) {
    builtins::math::math_func<ela::op::log>(s);
}

inline void builtins::math::pow(State &s) {
    builtins::math::math_func<ela::op::pow>(s);
}

inline void builtins::math::rand(State &s) {
    builtins::math::math_func<ela::op::rand>(s);
}

inline void builtins::math::factorial(State &s) {
    builtins::math::math_func_one_arg<int, ela::op::factorial>(s);
}

inline void builtins::math::round(State &s) {
    if(s.params.size() == 2 && utils::is_id_param(s.params[0])){
        const Variable var = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name) : utils::set_anon_number(s.params[1].name));
        s.set_var(
            Variable::Type::INT,
            s.params[0].name,
            std::to_string(static_cast<int>(std::round(std::stof(var.value))))
        );
        if(utils::is_anon_number(var)) s.rem_var(var);
        return;
    }
    throw std::runtime_error("MATH::ROUND -> Invalid args");
}


template<class T, class U, template <class> class Op>
void builtins::math::binary_op(State& s) {
    if(s.params.size() == 3 && utils::is_id_param(s.params[0])) {
        const Variable right = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name) : utils::set_anon_number(s.params[1].name));
        const Variable left = (utils::is_id_param(s.params[2]) ? s.get_var(s.params[2].name) : utils::set_anon_number(s.params[2].name));
        const Variable::Type type = (right.type > left.type ? right.type : left.type);
        std::string res;

        if(type == Variable::Type::INT) {
            Op<T> op;
            res = std::to_string(op(std::stoi(right.value), std::stoi(left.value)));
        }
        else if(type == Variable::Type::FLOAT) {
            Op<U> op;
            res = std::to_string(op(std::stoi(right.value), std::stoi(left.value)));
        }

        s.set_var(
            type,
            s.params[0].name,
            res
        );

        if(utils::is_anon_number(right)) s.rem_var(right);
        if(utils::is_anon_number(left)) s.rem_var(left);

        return;
    }
    throw std::runtime_error("MATH::BINARY_OPERATION -> Invalid args");
}

template<template <class> class Op>
void builtins::math::math_func(State &s) {
    if(s.params.size() == 3 && utils::is_id_param(s.params[0])) {
        const Variable right = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name) : utils::set_anon_number(s.params[1].name));
        const Variable left = (utils::is_id_param(s.params[2]) ? s.get_var(s.params[2].name) : utils::set_anon_number(s.params[2].name));
        const Variable::Type type = (right.type > left.type ? right.type : left.type);
        std::string res;

        if(type == Variable::Type::INT) {
            Op<int> op;
            res = std::to_string(op(std::stoi(right.value), std::stoi(left.value)));
        }
        else if(type == Variable::Type::FLOAT) {
            Op<float> op;
            res = std::to_string(op(std::stoi(right.value), std::stoi(left.value)));
        }

        s.set_var(type,s.params[0].name,res);

        if(utils::is_anon_number(right)) s.rem_var(right);
        if(utils::is_anon_number(left)) s.rem_var(left);
        return;
    }
    throw std::runtime_error("MATH::BINARY_OPERATION -> Invalid args");
}

template<class T, template <class> class Op>
void builtins::math::math_func_one_arg(State& s){
    if(s.params.size() == 2 && utils::is_id_param(s.params[0])) {
        const Variable var = (utils::is_id_param(s.params[1]) ? s.get_var(s.params[1].name) : utils::set_anon_number(s.params[1].name));
        const Variable::Type type = (var.type == Variable::Type::FLOAT ? Variable::Type::FLOAT : Variable::Type::INT);
        std::string res;

        if(type == Variable::Type::INT) {
            Op<T> op;
            res = std::to_string(op(std::stoi(var.value)));
        }
        else if(type == Variable::Type::FLOAT) {
            Op<T> op;
            res = std::to_string(op(std::stof(var.value)));
        }

        s.set_var(type, s.params[0].name, res);


        if(utils::is_anon_number(var)) s.rem_var(var);
        return;
    }
    throw std::runtime_error("MATH::FUNC_ONE_ARG -> Invalid args");
}