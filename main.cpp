#include "include/Lexer.hpp"
#include "include/Parser.hpp"
#include "include/Interpreter.hpp"

#include <windows.h>

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    try {
        const std::string path = argv[1];

        Lexer lex(utils::file_to_str(path));
        lex.tokenize();
        // lex.print_tokens();
        std::cout << std::endl;
        const auto tokens = lex.get_tokens();

        Parser parser(tokens);
        const auto functions = parser.get_functions();
        // parser.print_functions(functions);

        Interpreter interpreter(functions);
        interpreter.execute();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
