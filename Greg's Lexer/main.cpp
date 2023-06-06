#include <iostream>
#include "Lexer.h"
#include "Lexer.cpp"

using namespace std;


int main (int argc, char **argv){
    std::string filename;
    filename = argv[1];
    Lexer lexer = Lexer(filename);
}