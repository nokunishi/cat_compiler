#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#include "asm.h"
#include "token.h"

namespace fs = std::__fs::filesystem;

char * file_str(fstream &f) {
    stringstream s;
    string contents;

    s << f.rdbuf();
    string s_tmp = s.str();
    const char * s_const = s_tmp.c_str();
    return strdup(s_const);
}

void tokens_to_asm(const vector<Token> &tokens, int lno) {
    stringstream output;

    if (tokens.size() != 4 || tokens[0].type != Token::TokenType::animal ||
            tokens[1].type != Token::TokenType::action || 
            tokens[2].type != Token::TokenType::sep) {
        return;
    }

    string name;
    if (tokens[SEP_IDX].value == ".") {
        name = normal(tokens[STR_IDX].value);
    }
    if (tokens[SEP_IDX].value == "!") {
        name = normal(tokens[STR_IDX].value) + "!";
    }
    if (tokens[SEP_IDX].value == "!!") {
        name = demand(tokens[STR_IDX].value) + "!!";
    }
    create_asm("model.s", name, lno);
}


int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "specify input file" << endl;
        return EXIT_FAILURE;
    }

    DIR * dir = opendir("../out");
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir("../out", 0777);
    }

    fstream f(argv[1]);
    int i = 0;
    
    char * s_ = file_str(f);
    for (char * l = strtok(s_, "\n"); l != NULL; l = strtok(NULL, "\n")) {
        Token t;
        bool isCustom = false;

        if (strstr(l, "#define") != NULL) {
            isCustom = true;
            char * w = strtok(l, " ");
            char * animal = strtok(NULL, " ");
            char * sound = w = strtok(NULL, " ");
            
            Token::tokens.push_back(Token::TokenType::animal, animal);
        } 

        vector<Token> token = t.tokenize(l);
        tokens_to_asm(token, i);
        i++;
    }

    #ifdef __APPLE__
        for (const auto & entry: fs::directory_iterator("../out")) {
            string name = entry.path();
            string name_ = "";
            int i = 0;
            while (i < name.length() - 2) {
                name_ += name[i];
                i++;
            }

            const string cmd1 = "as " + name + " -o " + name_ + ".o";   
            const string cmd2 = "ld " + name_ + ".o -o " + name_ + " -l System -syslibroot " +
                "`xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64";
            
            system(cmd1.c_str());
            system(cmd2.c_str()); 
        }
    #endif 

    return EXIT_SUCCESS;
}