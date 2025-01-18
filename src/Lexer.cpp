#include "../include/Lexer.hpp"

void Lexer::add_token(const Token::Type &ty, const std::string &str) {
    this->tokens.push_back({
        .type = ty,
        .name = str
    });
}

void Lexer::add_token__char(const Token::Type &ty, const char &ch) {
    this->tokens.push_back({ty, utils::ctos(ch)});
}

void Lexer::add_token__separator(const char& ch) {
    this->tokens.push_back({Token::Type::SEPARATOR, utils::ctos(ch)});
}


Lexer::Lexer(const std::string &src) {
    this->source = src;
    this->tokens = {};
}

void Lexer::tokenize() {
    std::string temp_string;
    std::stack<char> container_stack;

    for(std::size_t i{}; i < this->source.length(); i++) {
        char cur_char = this->source[i];

        // comment
        if(utils::is_comment(cur_char)) {
            while((cur_char = this->source[++i]) != '\n');
        }

        // array
        if(utils::is_container__open(cur_char)) {
            container_stack.push(cur_char);
            temp_string += cur_char;
            cur_char = this->source[++i];

            while(!container_stack.empty()) {
                if(utils::is_container__open(cur_char)) {
                    container_stack.push(cur_char);
                } else if(utils::is_container__close(cur_char)) {
                    container_stack.pop();
                }

                if(std::isspace(cur_char)) {
                    cur_char = this->source[++i];
                    continue;
                }
                temp_string += cur_char;
                cur_char = this->source[++i];
            }
            this->add_token(Token::Type::CONTAINER, temp_string);
            this->add_token__separator(defines::sep::close::paren);
            temp_string.clear();
            continue;
        }

        // string
        if(utils::is_quote(cur_char)) {
            temp_string += cur_char;
            cur_char = this->source[++i];
            while(!utils::is_quote(cur_char)) {
                cur_char = this->source[i++];
                temp_string += cur_char;
            }
            this->add_token(Token::Type::STRING, temp_string);
            this->add_token__separator(defines::sep::close::paren);
            temp_string.clear();
            continue;
        }

        // params
        if(utils::is_sep(cur_char)) {
            if(!temp_string.empty()) {
                this->add_token(
                    (utils::is_number(temp_string) ? Token::Type::NUMBER : Token::Type::IDENTIFIER),
                    temp_string
                );
            }
            this->add_token__separator(cur_char);
            temp_string.clear();
            continue;
        }

        // end function
        if(cur_char == defines::sep::semicolon) {
            this->add_token(Token::Type::SEMICOLON, utils::ctos(cur_char));
            temp_string.clear();
            continue;
        }

        if(cur_char == '\n' || std::isspace(cur_char)) {
            continue;
        }

        temp_string += cur_char;
    }

    this->add_token(Token::Type::END, "\0");
}

void Lexer::print_tokens() const noexcept {
    for(const auto& [type, name] : this->tokens) {
        std::cout << static_cast<int>(type) << '\t' << name << std::endl;
    }
}

std::vector<Token> Lexer::get_tokens() const noexcept {
    return this->tokens;
}





