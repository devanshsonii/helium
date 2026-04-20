#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "generator.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
    // argv[1]: path to the .he file
    if(argc < 2) {
        std::cerr << "Invalid usage.\nCorrect Usage: Helium file.he\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    std::string content;
    std::vector<Token> tokens;
    Tokenizer tokenizer;

    while(std::getline(file, content)){
        tokens = tokenizer.tokenize(content);
    }

    Parser parser(std::move(tokens));
    std::optional<ExitNode> exit_node = parser.parse();
    
    if(exit_node.has_value()) {
        Generator generator(exit_node.value());
        generator.generate();
    } else {
        std::cerr << "Something went wrong while generating\n";
    }
    return 0;
}