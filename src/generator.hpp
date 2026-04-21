#pragma once
#include "parser.hpp"
#include <string>
#include <fstream>

class Generator {
public:
    Generator(ExitNode ext_node): exit_node(ext_node) {}

    void generate() {
        std::ofstream out("out.s");
        out << ".global _start\n";
        out << ".align 2\n";
        out << "_start:\n\tmov x0, " <<  std::get<IntLiteralNode>(exit_node.expr.var).tkn.value << "\n";
        out << "\tmov x16, 1\n\tsvc 0x80\n";
        out.close();
        system("as -arch arm64 -o out.o out.s");
        system("ld -o out out.o -lSystem -syslibroot `xcrun --show-sdk-path` -e _start -arch arm64");
        system("rm out.o out.s");
    }
private: 
    const ExitNode exit_node;
};