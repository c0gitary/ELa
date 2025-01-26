#pragma once

#include "typedefs.hpp"
#include "utils.hpp"
#include "defs.hpp"

#include <iostream>
#include <functional>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

namespace builtins {
    namespace internal {
        static void new_var(State&);
    }

    namespace io {
        static void print(State&);
        static void input(State&);
        static void clear(State&);
        static void pause(State&);
    }

    namespace file {
        static void create(State&);
        static void open(State&);
        static void remove(State&);
        static void read(State&);
        static void write(State&);
        static void move(State&);
    }

    namespace string {
        static void concat(State&);
        static void substring(State&);
        static void lenght(State&);
    }

    namespace time {
        static void current_date(State&);
        static void current_time(State&);
    }

    namespace math {
        static void mul(State&);
        // static void div(State&);
        // static void mod(State&);
        // static void sum(State&);
        // static void sub(State&);
    }


    inline static std::unordered_map<std::string, std::function<void(State&)>> __builtins {
        {defines::builtins::internal::new_var, builtins::internal::new_var},

        {defines::builtins::io::clear, io::clear},
        {defines::builtins::io::input, io::input},
        {defines::builtins::io::output, io::print},
        {defines::builtins::io::pause, io::pause},

        {defines::builtins::string::add, string::concat},
        {defines::builtins::string::lenght, string::lenght},
        {defines::builtins::string::substring, string::substring},

        {defines::builtins::time::cur_date, time::current_date},
        {defines::builtins::time::cur_time, time::current_time},

        // {defines::builtins::file::create, file::create},
        // {defines::builtins::file::open, file::open},
        // {defines::builtins::file::read, file::read},
        // {defines::builtins::file::write, file::write},
        // {defines::builtins::file::move, file::move},
        // {defines::builtins::file::remove, file::remove}
    };

}











inline void builtins::internal::new_var(State & s) {
    if(s.params.size() == 2) {
        const auto ty_var = utils::get_type_param(s.params[1]);
        if(ty_var != Variable::Type::IDENTIFIER)
            s.set_var(
                ty_var,
                s.params[0].name,
                s.params[1].name
            );
        else {
            if(s.contains(s.params[1].name)) {
                s.set_var(
                    s.get_value(s.params[1].name).type,
                    s.params[0].name,
                    s.get_value(s.params[1].name).value
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
    throw std::runtime_error("Invalid args");
}


inline void builtins::io::print(State & s) {
    for(std::size_t i{}; i < s.params.size(); i++) {
        const auto str = s.get_value(s.params[i].name).value;
        std::cout << str << ' ';
    }
    std::cout << std::endl;
}

inline void builtins::io::input(State &s) {
    if(s.params.size() == 1 && utils::is_id_param(s.params[0])) {
        std::string __input;
        std::getline(std::cin, __input);
        s.set_var(Variable::Type::STRING, s.params[0].name, __input);
        return;
    }
    throw std::runtime_error("IO::INPUT -> Count params != 2");
}

inline void builtins::io::pause(State &) {
    system("pause");
}

inline void builtins::io::clear(State &) {
    system("cls");
}

inline void builtins::string::concat(State &s) {
    if(s.params.size() == 3 && utils::is_id_param(s.params[0])) {
        if(s.contains(s.params[1].name) && s.contains(s.params[2].name)) {
            s.set_var(
                Variable::Type::STRING,
                s.params[0].name,
                utils::add_quotes(
                    utils::extract_content(s.get_value(s.params[1].name).value) + utils::extract_content(s.get_value(s.params[2].name).value)
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
        const std::string val = (s.contains(s.params[1].name) ? s.get_value(s.params[1].name).value : s.params[1].name);
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

        if (s.contains(s.params[1].name) && s.get_value(s.params[1].name).type == Variable::Type::STRING) {
            const std::string value = s.get_value(s.params[1].name).value;
            const std::string content = utils::extract_content(value);

            if (s.contains(s.params[2].name) && s.get_value(s.params[2].name).type == Variable::Type::INT) {
                const int start_pos = std::stoi(s.get_value(s.params[2].name).value);

                if (s.contains(s.params[3].name) && s.get_value(s.params[3].name).type == Variable::Type::INT) {
                    const int length = std::stoi(s.get_value(s.params[3].name).value);

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


