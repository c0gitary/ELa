#pragma once

#define __DEF__(ARG1, ARG2) inline static constexpr auto ARG1 = ARG2

namespace defines {
    namespace __internal {
        __DEF__(anon_number, "__anon__number__");
    }

    namespace sep {
        //separator

        namespace open {
            __DEF__(paren, '(');
            __DEF__(curly, '{');
        }

        namespace close {
            __DEF__(paren, ')');
            __DEF__(curly, '}');
        }

        __DEF__(comma, ',');
        __DEF__(dot, '.');
        __DEF__(semicolon, ';');
        __DEF__(quote, '\"');
        __DEF__(comment, '#');

        static bool is_open(const char &ch) {
            return (ch == open::paren || ch == open::curly);
        }

        static bool is_close(const char &ch) {
            return (ch == close::paren || ch == close::curly);
        }
    }

    namespace keywords::logic {
        __DEF__(__true, "ИСТИНА");
        __DEF__(__false, "ЛОЖЬ");
    }

    namespace builtins {
        // default functions

        namespace internal {
            __DEF__(new_var, "новая_переменная");
            __DEF__(rem_var, "удалить_переменную");
        }

        namespace io {
            // input - output
            __DEF__(output, "вывод");
            __DEF__(input, "ввод");
            __DEF__(clear, "очистить_вывод");
            __DEF__(pause, "пауза");
            __DEF__(new_line, "новая_строка");
        }

        namespace math {
            __DEF__(sum, "сложить");
            __DEF__(sub, "разность");
            __DEF__(mul, "умножить");
            __DEF__(div, "делить");
            __DEF__(mod, "остаток_от_деления");
            __DEF__(log, "логарифм");
            __DEF__(l_and, "логическое_и");
            __DEF__(l_or, "логическое_или");
            __DEF__(l_not, "логическое_не");
            __DEF__(rand, "случайное_число");
            __DEF__(round, "округление");
            __DEF__(pow, "степень");
            __DEF__(fact, "факториал");
        }

        namespace time {
            __DEF__(cur_date, "текущая_дата");
            __DEF__(cur_time, "текущее_время");
        }

        namespace file {
            __DEF__(create, "создать_файл");
            __DEF__(remove, "удалить_файл");
            __DEF__(open, "открыть_файл");
            __DEF__(read, "прочитать_файл");
            __DEF__(copy, "скопировать_файл");
            __DEF__(write, "написать_в_файл");
            __DEF__(add,  "добавить_в_файл");
            __DEF__(move , "переместить_файл");
            __DEF__(close, "закрыть_файл");
        }

        namespace folder {
            __DEF__(newfolder, "создать_папку");
            __DEF__(remfolder, "удалить_папку");
            __DEF__(movefolder, "переместить_папку");
        }

        namespace container {
        }

        namespace string {
            __DEF__(add, "сложить_строки");
            __DEF__(substring, "найти_подстроку");
            __DEF__(lenght, "длина_строки");
            __DEF__(find_string, "найти_строку");
            __DEF__(find_char, "найти_символ");
        }


        namespace flow {
            // stream
            __DEF__(loop, "цикл");
            __DEF__(repeat, "повторять");
        }
    }

    namespace errors {

        namespace main {
            __DEF__(__this__,  "[Ошибка]");
            __DEF__(extension, "Неверное расширение файла");
            __DEF__(args, "Неверное кол-во параметров");
        }

        namespace parser {
            __DEF__(__this__, "[Синтаксческая ошибка]");
            __DEF__(expected_char, "Ожидается символ");
            __DEF__(expected_id, "Ожидается тип токена: 'идентификатор'");
            __DEF__(unknown_type, "Неизвестный тип токена");
        }

        namespace runtime {
        }
    }
}
