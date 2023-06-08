#ifndef LEXER_H

#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <map>
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
    int at; // only the index of the start in all of the chacters total, not the (Ln,Col) 

    Token(){value = ""; type = TokenType::NIL; at = 0;}
    Token(char v , TokenType t, int n){value = v; type = t; at = n;}
    Token(std::string v , TokenType t, int n){value = v; type = t; at = n;}


    friend std::ostream& operator<<(std::ostream& os, Token& t) {
        std::vector<std::string> TypeStrings = {"space", "left parenthesis", "right parenthesis", "left curly", "right curly", "number",  "symbol", "variable", "letter", "identifier", "null"};
        return os << "Type: " << TypeStrings[t.type] << "\n Value: " << t.value << "\n At: " << t.at << std::endl;
    }

};


class Lexer {
public:
    
    Lexer(std::string filename);
    
    std::string filename;
    std::string fileContents = "";
    std::vector<Token> tokens;
    int cursor = 0;

    void readFile();
    Token createToken(char c);
    Token createToken(std::string phrase);
private:
    std::vector<std::string> splitWithCustomDelimiters(std::string s , std::string delimiters);
};

#endif // !LEXER_H