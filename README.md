# Helium - A Lightweight Proof of Concept Compiler

A minimal compiler written in C++ that translates Helium source code (`.he` files) into native ARM64 machine code.

## Features

- **Tokenization**: Lexical analysis that converts source code into tokens
- **Parsing**: Syntactic analysis that builds an Abstract Syntax Tree (AST)
- **Code Generation**: Generates ARM64 assembly code
- **Native Compilation**: Produces native executables for ARM64 architecture (macOS/Apple Silicon)

## Language Syntax

Helium currently supports a minimal set of language constructs:

```
return (integer_expression);
let variable_name = expression;
```

### Example Program

```helium
let x = 7;
return (x);
```

This declares a variable `x` with value 7 and returns it as the exit code.

## Building

```bash
g++-15 -std=c++17 -g src/main.cpp -I src -o build/helium
```

## Usage

```bash
./build/helium program.he
```

