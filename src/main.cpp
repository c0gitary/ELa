#include "include/Lexer.hpp"
#include "include/Parser.hpp"
#include "include/Interpreter.hpp"
#include "include/Error.hpp"

#include <windows.h>


bool __has_correct_ext(const std::string& filePath){
    const std::size_t dot_pos = filePath.find_last_of(".");
    if(dot_pos == std::string::npos) return false;
    const std::string fileExt = filePath.substr(dot_pos);
    return fileExt == ".ela";
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    if(argc < 2){
        return error::ThrowMain::error(error::type::Main::INVALID_ARGS, argv[0]);
    }

    const std::string path = argv[1];
    if(!__has_correct_ext(path)){
        return error::ThrowMain::error(error::type::Main::INALID_EXT, {});
    }

    Lexer lex(utils::file_to_str(path));
    lex.tokenize();

    Parser parser(lex.get_tokens());

    Interpreter interpreter(parser.get_functions());
    interpreter.execute();

    return 0;
}
