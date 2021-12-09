#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Please provide name of input file";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    /**
     * Lexer Stuffs
     */
    Lexer* lexer = new Lexer();

    std::stringstream file;
    file << in.rdbuf();

    std::string fileString = file.str();

    lexer->Run(fileString);

    /**
     * Parser Stuffs
     */
    Parser* parser = new class Parser();
    try
    {
        parser->ParseThisBaby(lexer->giveTokens());
        //parser->toString();
    }

    catch (const std::string &error) { std::cout << error << std::endl; }


    /**
     * Interpreter Stuffs
     */
    Interpreter* interpreter = new Interpreter(parser);
    interpreter->interpretThisBaby();

    delete lexer;

    return 0;
}