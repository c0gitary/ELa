#pragma once

#include <exception>
#include <string>
#include <tools/typedefs.hpp>
#include <tools/defs.hpp>
#include <format>
#include <iostream>

namespace error {

    namespace ThrowMain {
        static int error(const type::Main&& err, const std::string&& msg) {
            std::string msg_err =  defines::errors::main::__this__;
            switch(err) {
                case type::Main::INALID_EXT : {
                    msg_err += std::format(": {}", defines::errors::main::extension);
                    break;
                }
                case type::Main::INVALID_ARGS : {
                    msg_err = std::format(": {}\n  Правильное использование: {} <имя_файла>",
                        defines::errors::main::args,
                        msg
                    );
                    break;
                }
                default:
                    break;
            }
            std::cerr << msg_err << std::endl;
            return 1;
        }
    }


    namespace ThrowParser {
        template<class __TempReturnType__>
        static __TempReturnType__ error_unknown_type(const std::string& cur_token_type) {
            const std::string msgErr = std::format("{}: {}, текущий тип токен {}",
                defines::errors::parser::__this__,
                defines::errors::parser::expected_char,
                cur_token_type
            );
            std::cerr << msgErr << std::endl;
            std::exit(1);
        }

        template<class __TempReturnType__>
        static __TempReturnType__ error_expected_id(const std::string& cur_token, const std::string& ty_tok) {
            const std::string msgErr = std::format("{}: {}, текущий токен '{}', текущий тип токена '{}'",
                defines::errors::parser::__this__,
                defines::errors::parser::expected_char,
                cur_token,
                ty_tok
            );
            std::cerr << msgErr << std::endl;
            std::exit(1);
        }

        template<class __TempReturnType__>
        static __TempReturnType__ error_expected_char(const char& expected_ch, const char& cur_ch) {
            const std::string msgErr = std::format("{}: {} '{}', но текущий символ '{}'",
                defines::errors::parser::__this__,
                defines::errors::parser::expected_char,
                expected_ch,
                cur_ch
            );
            std::cerr << msgErr << std::endl;
            std::exit(1);
        }
    }

}
