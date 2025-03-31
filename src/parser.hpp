#pragma once
#include "tokenizer.hpp"

// these are the AST nodes
// we currently only have expression and exit nodes 
struct ExprNode {
    Token int_lit; // what and why is this? -> derived from the grammar, refer to grammar for explanations on why we have structs this way
};

struct ExitNode {
    ExprNode expr;
};

class Parser {
public:
    Parser(std::vector<Token> tkns) 
    : tokens(std::move(tkns)) {}
// what does a parser return? -> a parse tree (need nodes and stuff for the tree)
    std::optional<ExprNode> parseExpr() {
        if(peek().has_value() && peek().value().type == TokenType::INT_LITERAL) {
            return ExprNode{.int_lit = consume()};
        } else {
            return {};
        }
    }
    std::optional<ExitNode> parse() {
        // what is this function?
        std::optional<ExitNode> exit_node;
        while(peek().has_value()) {
            if(peek().value().type == TokenType::_RETURN) {
                consume();
                if(auto expr = parseExpr()) {
                    exit_node = ExitNode {.expr = expr.value()};
                    return exit_node;
                } else {
                    std::cerr << "Something went wrong in the parser.\n";
                    exit(EXIT_FAILURE);
                }
            } else {
                consume();
            }
        }
        std::cerr << "Something went wrong in parse.\n";
        return {};
    }


private:
    std::optional<Token> peek(int val = 1) {
        if(index + val > tokens.size()) {
            return {};
        } else {
            return tokens[index];
        }
    }
    Token consume() {
        return tokens[index++];
    }
    std::vector<Token> tokens;
    int index = 0;
}; 