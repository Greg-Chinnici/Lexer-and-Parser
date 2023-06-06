#include "Lexer.h"

Lexer::Lexer(std::string file) {
    filename = file;
    readFile();
}

void Lexer::readFile() {
    std::ifstream file;
    file.open(filename);
    std::vector <std::string> lines;

    if(file.is_open()){
        std::string line;   

        std::ifstream fin(filename);
        while(getline(file,line)){
            lines.push_back(line);
            fileContents.append(line);
        }
        file.close();
    }

    for (std::string line : lines){
        std::vector <std::string> cleanLine = splitWithCustomDelimiters(line , " (){}+=*/^%");  // spaces , parens , math symbols    

        for (auto phrase : cleanLine){
            if (phrase.length() < 2){tokens.push_back(createToken(phrase[0]));}                 // character case
            else{tokens.push_back(createToken(phrase));}                                        // full string check
        }
    }
}

std::vector<std::string> Lexer::splitWithCustomDelimiters(std::string s , std::string delimiters) {
    std::vector<std::string> result;
    std::size_t last_pos = 0;
    for (std::size_t i = 0 ; i < s.size() ; ++i)
    {
        if ( delimiters.find(s[i]) != delimiters.npos)
        {
            result.push_back(s.substr(last_pos,i-last_pos));
            ++i;
            last_pos = i;
        }
    }

    return result;
}

Token Lexer::createToken(char c) {
    TokenType type;
    char val = c;

    switch (c){
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

    if (std::isalpha(c)){type = TokenType::VARIABLE;}

    Token t = Token(val, type);
    std::cout << t << std::endl;
    return t;
}

Token Lexer::createToken(std::string s) {
    TokenType type;
    std::string val = s;

    std::string identifers = " int  char  string  float  double  ";
    if (identifers.find(" "+s+" ") != std::string::npos){type = TokenType::IDENTIFIER;} 

    Token t = Token(val, type);
    std::cout << t << std::endl;
    return t;
}