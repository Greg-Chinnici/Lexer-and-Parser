#include "Lexer.h"

Lexer::Lexer(std::string file){
    filename = file;
    readFile();
}

void Lexer::readFile(){
    std::ifstream file;
    file.open(filename);
    if(file.is_open()){
        file >> fileContents;
        file.close();
    }

    for (char c: fileContents){
        tokens.push_back(createToken(c));
    }
}

Token Lexer::createToken(char c){
    TokenType type;
    char val = c;

    switch (c)
    {
    case ' ':
        type = TokenType::SPACE;
        break;
    case '(':
        type = TokenType::L_PAREN;
        break;
    case ')':
        type = TokenType::R_PAREN;
        break;
    case '{':
        type = TokenType::L_CURLY;
        break;
    case '}':
        type = TokenType::R_CURLY;
        break;
    default:
        type = TokenType::NIL;
        break;
    }

    std::string mathSymbols = "+=*/^%";
    if (mathSymbols.find(c) != std::string::npos){type = TokenType::SYMBOL;}

    if (std::isalpha(c)){type = TokenType::LETTER;}

    Token t = Token(val, type);
    std:: cout << t << std::endl;
    return t;
}