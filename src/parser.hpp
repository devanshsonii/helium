#pragma once
#include <vector>
#include <variant>
#include "tokenizer.hpp"

// these are the AST nodes
// we currently only have expression and exit nodes 
/*
updated grammar:
    we need the following nodes: 
        ProgramNode -> vector<LineNode> nodes
        LineNode -> ExitNode | IdentifierNode
        ExitNode -> ExpressionNode
        ExpressionNode -> IntLiteralNode | IdentifierNode
        IdentifierNode
        IntLiteralNode

*/
struct ExprNode {
    std::variant<IntLiteralNode, IdentifierNode> var;
};

struct ExitNode {
    ExprNode expr;
};


struct ProgramNode {
    std::vector<LineNode> linenodes;

};
struct LineNode {
    std::variant<ExitNode, IdentifierNode> var;
};
struct IdentifierNode{

};
struct IntLiteralNode {
    Token tkn;
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
    // see if we have (, return, ), ; -> in this order
    std::optional<ExitNode> parse() {
        // what is this function?
        std::optional<ExitNode> exit_node;
        while(peek().has_value()) {
            if(peek().value().type == TokenType::_RETURN && peek(1).has_value() && peek(1).value().type == TokenType::OPEN_PAREN) {
                consume();
                consume();
                if(auto node = parseExpr()) {
                    exit_node = ExitNode{.expr = node.value()};
                } else {
                    std::cerr << "Error processing the expression\n";
                    exit(EXIT_FAILURE);
                }
            }
            if(peek().has_value() && peek().value().type == TokenType::CLOSE_PAREN) {
                consume();
            } else {
                std::cerr << "Expected `)`\n";
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type == TokenType::SEMI_COLON) {
                consume();
                return exit_node;
            } else {
                std::cerr << "Expected `;`\n";
                exit(EXIT_FAILURE); 
            }
        }
        std::cerr << "Something went wrong in the parser.\n";
        return {};
    }


private:
    std::optional<Token> peek(int val = 0) {
        if(index + val >= tokens.size()) {
            return {};
        } else {
            return tokens[index+val];
        }
    }
    Token consume() {
        return tokens[index++];
    }
    std::vector<Token> tokens;
    int index = 0;
}; 