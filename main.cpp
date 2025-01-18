#include "include/Lexer.hpp"
#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const auto path = R"(E:\dev_scripts\ela_git\ELa\test.ela)";
    // auto src = utils::file_to_str(path);
    // for(const char& ch : src) {
    //     std::cout << ch << std::endl;
    // }

    Lexer lex(utils::file_to_str(path));
    lex.tokenize();
    lex.print_tokens();

    return 0;
}
