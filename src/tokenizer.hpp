#pragma once
#include <optional>

enum class TokenType {
    _RETURN,
    INT_LITERAL,
    SEMI_COLON,
    OPEN_PAREN,
    CLOSE_PAREN
};

struct Token {
    TokenType type;
    std::string value;
};


class Tokenizer {
public:
    std::vector<Token> tokenize(std::string &inp) {
        this->src = inp;
        std::string buf;
        std::vector<Token> tokens;
        while(peek().has_value()) {
            if(isalpha(peek().value())) {
                buf += consume();
                while(isalpha(peek().value())) {
                    char temp = peek().value();
                    buf += consume();
                }
                if(buf == "return") {
                    tokens.push_back({.type = TokenType::_RETURN, .value = buf});
                    buf.clear();
                }   
            } else if(isdigit(peek().value())) {
                buf = consume();
                while(isdigit(peek().value())) {
                    buf += consume();
                }
                tokens.push_back({.type = TokenType::INT_LITERAL, .value = buf});
                buf.clear();
            } else if(isspace(peek().value())) {
                consume();
            } else if(peek().value() == '(') {
                tokens.push_back({.type = TokenType::OPEN_PAREN});
                consume();
            } else if(peek().value() == ')') {
                tokens.push_back({.type = TokenType::CLOSE_PAREN});
                consume();
            } else if(peek().value() == ';') {
                tokens.push_back({.type = TokenType::SEMI_COLON, .value = ";"});
                consume();
                buf.clear();
            } else {
                std::cerr << "Unexpected token received.\n";
                exit(EXIT_FAILURE);
            }
        }
        return tokens;
    }
private:
    inline std::optional<char> peek(int val = 0) const {
        if(index + val >= src.length()) {
            return {};
        } else {
            return src[index+val];
        }
    }
    inline char consume() {
        return src[index++];
    }
    std::string src;
    int index = 0;
};
