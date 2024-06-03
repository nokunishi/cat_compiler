#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

#include "animal.h"

using namespace std;

const int ACTION_IDX = 0;
const int SEP_IDX = 1;
const int STR_IDX = 2;


class Token {
    int parseStr(vector<Token> &tokens, const string&str, int);
    int parseSep(vector<Token> &tokens, const string&str, int);
    int parseAnimal(vector<Token> &tokens, vector<Animal>, const string&str, int);
    
    public:
    enum TokenType {
        action,
        sep,
        str
    };
    TokenType type;
    string value;

    Token();
    Token(TokenType t, string v);
    vector<Token> tokenize(const string &str, vector<Animal>);
};

#endif