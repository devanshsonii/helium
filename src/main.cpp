#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

enum class Tokens {
    _RETURN,
    INT_LITERAL,
    SEMI_COLON
};

struct Token {
    Tokens type;
    std::string value;
};

void tokenize(std::string &str, std::vector<Token> &tokens) {
    // str is a single complete line 
    // process the line and append the tokens to the tokens vectors.
    std::string buf;
    for (int i = 0; i < str.length(); i++) {
        const char c = str[i];
        if(isalpha(c)) {
            buf += c;
            i++;
            while(isalpha(str[i])){
                buf += str[i];
                i++;
            }
            i--;
            if(buf == "return") {
                tokens.push_back({.type = Tokens::_RETURN, .value = buf});
                buf = "";
            }
        } else if(isdigit(c)) {
            buf += c;
            i++;
            while(isdigit(str[i])) {
                buf += str[i];
                i++;
            }
            i--;
            tokens.push_back({.type = Tokens::INT_LITERAL, .value = buf});
            buf = "";
        } else if(isspace(c)) {
            continue;
        } else if(c == ';') {
            tokens.push_back({.type = Tokens::SEMI_COLON, .value = ";"});
        } else {
            std::cerr << "Something went wrong!" << "\n";
        }
    }
    
}

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
    std::ifstream file(argv[1]);
    std::string content;
    std::vector<Token> tokens;
    while(std::getline(file, content)){
        tokenize(content, tokens);
    }
    write_to_assembly(tokens);
    return 0;
}