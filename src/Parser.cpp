#include "../include/Parser.hpp"

std::string Parser::parse_id() {
    if(this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type == Token::Type::IDENTIFIER) {
        return  this->tokens[this->cur_token++].name;
    }
    throw std::runtime_error("Expected identifier");
}

void Parser::expect(Token::Type &&type, char expected_char) {
    if(this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type == type && this->tokens[this->cur_token].name[0] == expected_char) {
        this->cur_token++;
    } else {
        throw std::runtime_error("Expected: " + std::string(1, expected_char));
    }
}

bool Parser::eq_token_type(Token::Type &&type) const {
    return (this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type == type);
}

std::vector<Parameter> Parser::parse_parameters() {
    std::vector<Parameter> params;
    while(this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type != Token::Type::SEPARATOR) {
        params.push_back(this->parse_parameter());
        if (this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type == Token::Type::SEPARATOR && this->tokens[this->cur_token].name[0] == defines::sep::comma) {
            this->cur_token++;
        }
    }
    return params;
}

Parameter Parser::parse_parameter() {
    Parameter param;
    param.type = this->parse_type();
    param.name = this->tokens[this->cur_token++].name;
    return param;
}

Parameter::Type Parser::parse_type() const {
    if(this->eq_token_type(Token::Type::NUMBER)) {
        return Parameter::Type::NUMBER;
    }
    if(this->eq_token_type(Token::Type::STRING)) {
        return Parameter::Type::STRING;
    }
    if(this->eq_token_type(Token::Type::CONTAINER)) {
        return Parameter::Type::CONTAINER;
    }
    if(this->eq_token_type(Token::Type::IDENTIFIER)) {
        return Parameter::Type::IDENTIFIER;
    }

    throw std::runtime_error("Unknow type");
}

Parser::Parser(const std::vector<Token> &__tokens)
    :   tokens(__tokens), cur_token(0) {}

std::vector<Function> Parser::get_functions() noexcept {
    return this->parse_functions();
}

Function Parser::parse_function() {
    Function __function;

    __function.name = this->parse_id();

    this->expect(Token::Type::SEPARATOR, defines::sep::open::paren);
    __function.params = this->parse_parameters();

    this->expect(Token::Type::SEPARATOR, defines::sep::close::paren);
    this->expect(Token::Type::SEMICOLON, defines::sep::semicolon);

    return __function;
}

std::vector<Function> Parser::parse_functions() {
    std::vector<Function> functions;
    while(this->cur_token < this->tokens.size() && this->tokens[this->cur_token].type != Token::Type::END) {
        functions.push_back(this->parse_function());
    }
    return functions;
}


