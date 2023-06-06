#ifndef LEXER_H

#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <fstream>

typedef enum 
{
    SPACE,
    L_PAREN,
    R_PAREN,
    L_CURLY,
    R_CURLY,
    NUMBER,
    SYMBOL,
    VARIABLE,
    LETTER,
    IDENTIFIER,
    NIL
} TokenType;

typedef struct Token
{
    std::string value;
    TokenType type;

    Token(){Token t; t.value = ""; t.type = TokenType::NIL;}
    Token(char value , TokenType type){Token t; t.value = value; t.type = type;}
    Token(std::string value , TokenType type){Token t; t.value = value; t.type = type;}


    friend std::ostream& operator<<(std::ostream& os, Token& t) {
        std::vector<std::string> TypeStrings = {"space", "left parenthesis", "right parenthesis", "left curly", "right curly" , "number",  "symbol", "variable", "letter", "identifier" , "null"};
        return os << "Type: " << TypeStrings[t.type] << "\n Value: " << t.value << std::endl;
    }

};


class Lexer {
public:
    std::string filename;
    std::string fileContents = "";
    std::vector<Token> tokens;
    int cursor = 0;

    Lexer(std::string filename);

    void readFile();
    Token createToken(char c);
    Token createToken(std::string phrase);
private:
    std::vector<std::string> splitWithCustomDelimiters(std::string s , std::string delimiters);
};

#endif // !LEXER_H