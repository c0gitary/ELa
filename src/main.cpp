#include "include/Lexer.hpp"
#include "include/Parser.hpp"
#include "include/Interpreter.hpp"

#include <windows.h>
#include <exception>

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    try {
        const std::string path = argv[1];

        Lexer lex(utils::file_to_str(path));
        lex.tokenize();
        // lex.print_tokens();

        Parser parser(lex.get_tokens());

        Interpreter interpreter(parser.get_functions());
        interpreter.execute();

    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
