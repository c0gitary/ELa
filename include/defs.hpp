#pragma once

#include <array>

namespace defines {

    namespace sep { //separator

        namespace open {
            inline static constexpr auto paren = '(';
            inline static constexpr auto square = '[';
            inline static constexpr auto curly = '{';
        }

        namespace close {
            inline static constexpr auto paren = ')';
            inline static constexpr auto square = ']';
            inline static constexpr auto curly = '}';
        }

        inline static constexpr auto comma = ',';
        inline static constexpr auto dot = '.';
        inline static constexpr auto semicolon = ';';
        inline static constexpr auto quote = '\"';
        inline static constexpr auto comment = '#';

        static bool is_open(const char& ch) {
            return (ch == open::paren ||
                    ch == open::square ||
                    ch == open::curly);
        }

        static bool is_close(const char& ch) {
            return (ch == close::paren ||
                    ch == close::square ||
                    ch == close::curly);
        }

    }

    namespace keywords {
        inline static constexpr auto __true = "ИСТИННА";
        inline static constexpr auto __false = "ЛОЖЬ";
    }

    namespace builtins { // default functions

        namespace internal {
            inline static constexpr auto new_var = "новая_перемення";
        }

        namespace io { // input - output
            inline static constexpr auto output = "вывод";
            inline static constexpr auto input = "ввод";
            inline static constexpr auto clear = "очистить_ввод";
            inline static constexpr auto pause = "пауза";
        }

        namespace math {
            inline static constexpr auto sum    = "сумма";
            inline static constexpr auto sub    = "вычитание";
            inline static constexpr auto mul    = "умножение";
            inline static constexpr auto div    = "деление";
            inline static constexpr auto mod    = "остаток_от_деления";
            inline static constexpr auto log    = "логарифм";
            inline static constexpr auto l_and  = "логическое_и";
            inline static constexpr auto l_or   = "логическое_или";
            inline static constexpr auto l_not  = "логическое_не";
            inline static constexpr auto rand   = "рандомное_число";
            inline static constexpr auto round  = "округление";
        }

        namespace time {
            inline static constexpr auto cur_date        = "текущая_дата";
            inline static constexpr auto cur_time        = "текущее_время";
            inline static constexpr auto format_date     = "формат_даты";
            inline static constexpr auto format_time     = "формат_времени";
        }

        namespace file {
            inline static constexpr auto create = "создать";
            inline static constexpr auto remove = "удалить";
            inline static constexpr auto open = "открыть";
            inline static constexpr auto read = "прочитать";
            inline static constexpr auto copy = "скопировать";
            inline static constexpr auto write = "написать";
            inline static constexpr auto move = "переместить";
            inline static constexpr auto close = "закрыть";
        }

        namespace container { // arrays

        }

        namespace string {
            inline static constexpr auto add            = "сложить_строки";
            inline static constexpr auto understring    = "подстрока";
            inline static constexpr auto lenght         = "длина_строки";
            inline static constexpr auto find_string    = "найти_строку";
            inline static constexpr auto find_char      = "найти_символ";
        }

        namespace flow { // stream
            inline static constexpr auto __if = "если";
            inline static constexpr auto __for = "цикл";
            // inline static constexpr auto __while = "";
        }

        inline static constexpr  std::array __all_builtins {
            internal::new_var,

            io::clear,
            io::input,
            io::output,
            io::pause,

            math::sum,
            math::sub,
            math::mul,
            math::div,
            math::mod,
            math::log,
            math::l_and,
            math::l_or,
            math::l_not,
            math::rand,
            math::round,

            time::cur_date,
            time::cur_time,
            time::format_date,
            time::format_time,

            string::add,
            string::understring,
            string::lenght,
            string::find_string,
            string::find_char,

            flow::__if,
            flow::__for
        };

    }


}
