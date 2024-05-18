#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

#include "asm.h"
#include "token.h"

void tokens_to_asm(const vector<Token> &tokens, int lno) {
    stringstream output;

    if (tokens.size() != 3 || tokens[0].type != Token::TokenType::_print ||
            tokens[1].type != Token::TokenType::sep) {
        return;
    }

    string name;
    if (tokens[1].value == ".") {
        name = tokens[2].value;
    }
    if (tokens[1].value == "!") {
        name = exclaim(tokens[2].value);
    }
    if (tokens[1].value == "!!") {
        name = demand(tokens[2].value);
    }
    create_asm("model.s", name, lno);
}


char * file_str(fstream &f) {
    stringstream s;
    string contents;

    s << f.rdbuf();
    string s_tmp = s.str();
    const char * s_const = s_tmp.c_str();
    return strdup(s_const);
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "specify input file" << endl;
        return EXIT_FAILURE;
    }

    fstream f(argv[1]);
    Token t;
    int i = 0;
    
    char * s_ = file_str(f);
    for (char * l = strtok(s_, "\n"); l != NULL; l = strtok(NULL, "\n")) {
        vector<Token> token = t.tokenize(l);
        tokens_to_asm(token, i);
        i++;
    }

    return EXIT_SUCCESS;
}