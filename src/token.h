#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

using namespace std;


class Token {
    int returnVal(vector<Token> &tokens, const string&str, int i);
    int parseSep(vector<Token> &tokens, const string&str, int i);
    
    public:
    enum TokenType {
        _print,
        _str,
        sep,
    };
    TokenType type;
    string value;

    Token();
    Token(TokenType t, string v);
    vector<Token> tokenize(const string &str);
};


#endif