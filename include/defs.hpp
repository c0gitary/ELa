#pragma once

namespace defines {

    namespace __internal {
        inline static constexpr auto anon_number = "__anon__number__";
    }

    namespace sep { //separator

        namespace open {
            inline static constexpr auto paren  = '(';
            inline static constexpr auto square = '[';
            inline static constexpr auto curly  = '{';
        }

        namespace close {
            inline static constexpr auto paren  = ')';
            inline static constexpr auto square = ']';
            inline static constexpr auto curly  = '}';
        }

        inline static constexpr auto comma      = ',';
        inline static constexpr auto dot        = '.';
        inline static constexpr auto semicolon  = ';';
        inline static constexpr auto quote      = '\"';
        inline static constexpr auto comment    = '#';

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
    
        namespace logic {
            inline static constexpr auto __true  = "ИСТИННА";
            inline static constexpr auto __false = "ЛОЖЬ";
        }

    }

    namespace builtins { // default functions

        namespace internal {
            inline static constexpr auto new_var = "новая_переменная";
            inline static constexpr auto rem_var = "удалить_переменную";
        }

        namespace io { // input - output
            inline static constexpr auto output = "вывод";
            inline static constexpr auto input  = "ввод";
            inline static constexpr auto clear  = "очистить_вывод";
            inline static constexpr auto pause  = "пауза";
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
            inline static constexpr auto rand   = "случайное_число";
            inline static constexpr auto round  = "округление";
            inline static constexpr auto pow    = "степень";
            inline static constexpr auto fact   = "факториал";
        }

        namespace time {
            inline static constexpr auto cur_date        = "текущая_дата";
            inline static constexpr auto cur_time        = "текущее_время";
        }

        namespace file {
            inline static constexpr auto create = "создать_файл";
            inline static constexpr auto remove = "удалить_файл";
            inline static constexpr auto open   = "открыть_файл";
            inline static constexpr auto read   = "прочитать_файл";
            inline static constexpr auto copy   = "скопировать_файл";
            inline static constexpr auto write  = "написать_в_файл";
            inline static constexpr auto add    = "добавить_в_файл";
            inline static constexpr auto move   = "переместить_файл";
            inline static constexpr auto close  = "закрыть_файл";
        }

        namespace folder {
            inline static constexpr auto newfolder  = "новая_папка"; 
            inline static constexpr auto remfolder  = "удалить_папку"; 
        }

        namespace container {
            
            namespace array {
                inline static constexpr auto append = "добавление_в_массив";
                inline static constexpr auto remove = "удаление_из_массива";
                inline static constexpr auto get_element = "получения_элемента";
                inline static constexpr auto contains = "содержание_элемента";
                inline static constexpr auto length = "длина_массива";
                inline static constexpr auto reserve = "обратный_массив";
                inline static constexpr auto clear = "очищение_массива";
                inline static constexpr auto pop = "удаление_элемента";
                inline static constexpr auto sort = "сортировка_массива";
            }
            
            namespace string {
                inline static constexpr auto add            = "сложить_строки";
                inline static constexpr auto substring      = "найти_подстроку";
                inline static constexpr auto lenght         = "длина_строки";
                inline static constexpr auto find_string    = "найти_строку";
                inline static constexpr auto find_char      = "найти_символ";
            }

        }


        namespace flow { // stream
            // inline static constexpr auto __if  = "если";
            inline static constexpr auto loop = "цикл";
            // inline static constexpr auto __while = "";
        }


    }


}
