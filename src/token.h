#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

using namespace std;

const int ANIMAL_IDX = 0;
const int SOUND_IDX = 1;
const int ACTION_IDX = 2;
const int SEP_IDX = 3;
const int STR_IDX = 4;


class Token {
    int parseStr(vector<Token> &tokens, const string&str, int i);
    int parseSep(vector<Token> &tokens, const string&str, int i);
    int parseAnimal(vector<Token> &tokens, const string&str, int i);
    
    public:
    enum TokenType {
        animal,
        action,
        sep,
        str
    };
    TokenType type;
    string value;

    Token();
    Token(TokenType t, string v);
    vector<Token> tokenize(const string &str);
};


#endif