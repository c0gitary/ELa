#include "include/Lexer.hpp"
#include "include/Parser.hpp"

#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    const auto path = R"(E:\dev_scripts\ela_git\ELa\test.ela)";

    Lexer lex(utils::file_to_str(path));
    lex.tokenize();
    // lex.print_tokens();
    const auto tokens = lex.get_tokens();

    Parser parser(tokens);

    for(auto fns = parser.get_functions(); const auto&[name, params] : fns) {
        std::cout << "Имя функции: " << name << std::endl;
        std::cout << "Параметры функции: " << std::endl;
        for(const auto& [type, name] : params) {
            std::cout << "Имя параметра: " << name << '\t' << "Тип параметра: " << utils::get_type_value(type) << std::endl;
        }
        std::cout << std::endl;
    }


    return 0;
}
