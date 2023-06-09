#include "Lexer.h"

Lexer::Lexer(std::string file) {
    filename = file;
    readFile();
}

void Lexer::readFile() {
    std::ifstream file;
    file.open(filename);
    std::vector <std::string> lines;

    if(file.is_open())
    {
        std::string line;   


        std::ifstream fin(filename);
        while(getline(file,line))
        {
            lines.push_back(line);
            fileContents.append(line);
        }
        file.close();
    }

    for (std::string line : lines){
        // current delimitters: spaces , parens , math symbols
        std::vector <std::string> cleanLine = splitWithCustomDelimiters(line , " (){}+=*/^%");  

        std::vector<Token> LineOfTokens;

        // create and store the token, also move the cursor
        for (auto phrase : cleanLine)                                                           
        {

            // character case                                             
            if (phrase.length() < 2){LineOfTokens.push_back(createToken(phrase[0])); cursor++;}   
            // full string case
            else{LineOfTokens.push_back(createToken(phrase)); cursor+=phrase.length();}
        }

        tokens.push_back(LineOfTokens);
    }
}

//TODO FIX THIS TO ADD THE DELIMITTER TOO
std::vector<std::string> Lexer::splitWithCustomDelimiters(std::string s , std::string delimiters) {
    std::vector<std::string> result;
    std::size_t last_pos = 0;
    for (std::size_t i = 0 ; i < s.size() ; ++i)
    {
        if ( delimiters.find(s[i]) != delimiters.npos)
        {
            result.push_back(s.substr(last_pos,i-last_pos));
            //++i;
            last_pos = i;
        }
    }

    return result;
}

Token Lexer::createToken(char c) {

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

    {
    // math symbols
    std::string mathSymbols = "+=*/^%";                                                        
    if (mathSymbols.find(c) != std::string::npos){type = TokenType::SYMBOL;} 
    }
    
    {
    // variables
    if (std::isalpha(c)){type = TokenType::VARIABLE;}
    }
  

    Token t = Token(val, type, cursor);
    std::cout << t << std::endl;
    return t;
}

Token Lexer::createToken(std::string s) {
    TokenType type = TokenType::VARIABLE;
    std::string val = s;
   
    {
    // list of intentifiers (variable types)
    std::string identifiers = " int  char  string  float  double ";
    if (identifiers.find(" "+s+" ") != std::string::npos){type = TokenType::IDENTIFIER;}

    // does the same thing but maybe faster???
    std::map<std::string,int> identifiersMAP = { {"int",1},  {"char",1},  {"string",1}, {"float",1},  {"double",1} }; 
    if (identifiersMAP.find(s) == identifiersMAP.end()){type = TokenType::IDENTIFIER;}
    }

    Token t = Token(val, type, cursor);
    std::cout << t << std::endl;
    return t;
}

// will probably have lots of error cases
void Lexer::WhatIsAt(int c){
    int endOfLine = c;
    while(true)
    {
        if (fileContents[endOfLine] == '\n'){break;}
        endOfLine++;
    }

    int startOfLine = endOfLine-1;
    while(true)
    {
        if (fileContents[startOfLine] == '\n'){break;}
        startOfLine--;    
    }

    int lineCnt = 0;
    for (int i = 0 ; i < fileContents.length() ; i++)
    {
        if (fileContents[i] == '\n'){lineCnt++;}
        if (i == c){break;}
    }

    std::string restOfLine = fileContents.substr(startOfLine , endOfLine-startOfLine);

    std::cout << "Line at " << lineCnt << ": " << restOfLine << std::endl;
    for (int i = 0 ; i < tokens[lineCnt].size() ; i++)
    {
        std::cout << tokens[lineCnt][i] << std::endl;
    }
}