#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include "tokenizer.hpp"

void write_to_assembly(std::vector<Token> &tokens) {
    std::ofstream out("out.s");
    out << ".global _start\n";
    out << ".align 2\n";
    out << "_start:\n\tmov x0, " << stoi(tokens[1].value) << "\n";
    out << "\tmov x16, 1\n\tsvc 0x80\n";
    out.close();
    system("as -arch arm64 -o out.o out.s");
    system("ld -o out out.o -lSystem -syslibroot `xcrun --show-sdk-path` -e _start -arch arm64");
    system("rm out.o out.s");
}

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
    write_to_assembly(tokens);
    return 0;
}