#pragma once

#include "typedefs.hpp"
#include "defs.hpp"
#include "utils.hpp"

#include <stdexcept>

class Parser {
    std::vector<Token> tokens;
    std::size_t cur_token;

    std::string parse_id();

    void expect(Token::Type&& type, char expected_char);

    bool eq_token_type(Token::Type&& type) const;

    std::vector<Parameter> parse_parameters();

    Parameter parse_parameter();

    Parameter::Type parse_type() const;

    Function parse_function();

    std::vector<Function> parse_functions();

public:
    explicit Parser(const std::vector<Token>& __tokens);
    std::vector<Function> get_functions() noexcept;
};


