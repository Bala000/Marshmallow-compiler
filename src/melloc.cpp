//
// Created by Ejaz on 4/27/2018.
//

#include <string>
#include "utils/symbolTable.h"
#include "compiler/parser.h"
#include "compiler/lexer.h"
#include "compiler/bytecode.h"
#include "runtime/runtime.h"

int main(int argc, char** argv) {


    if(argc != 2)
    {
        std::cout << "Invalid input. e.g. melloc <input.mlw>"<<std::endl;
         return 0;
    }

    std::string program = argv[1];

    std::vector<char> programbuff;
    char ch;
    std::fstream fin(program, std::fstream::in);
    while (fin >> std::noskipws >> ch) {
        programbuff.push_back(ch);
    }
    fin.close();

    Lexer *lexer = new Lexer(programbuff);
    std::vector<std::string> tokens = lexer->Tokenize();

    SymbolTable *symbolTable = new SymbolTable();
    Parser *parser = new Parser(tokens);
    Node* ast = parser->getProgram(*symbolTable);

    std::vector<int> byteCode;
    bytecode *b = new bytecode(symbolTable);
    b->generateByteCode(ast,ast->getType(),byteCode);

    delete ast;
    delete symbolTable;
    delete parser;
    delete b;

    std::string output = program.replace(program.length()-3,3,"o") ;

    const char* pointer = reinterpret_cast<const char*>(&byteCode[0]);
    size_t bytes = byteCode.size() * sizeof(byteCode[0]);
    std::ofstream opstream;
    opstream.open(output,std::ios::out | std::ios::binary);
    opstream.write(pointer, bytes);
    opstream.close();
    return 0;
}
