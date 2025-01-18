#pragma once

#include "typedefs.hpp"
#include "utils.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <stack>

class Lexer {
    std::vector<Token> tokens;
    std::string source;

    void add_token(const Token::Type& ty, const std::string& str);
    void add_token__char(const Token::Type& ty, const char& ch);
    void add_token__separator(const char& ch);

public:
    explicit Lexer(const std::string& src);

    void tokenize();

    void print_tokens() const noexcept;

    std::vector<Token> get_tokens() const noexcept;
};