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
#include "animal.h"

namespace fs = std::__fs::filesystem;

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

    DIR * dir = opendir("../out");
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir("../out", 0777);
    }

    fstream f(argv[1]);
    int i = 0;
    vector<Animal> animals;
    
    char * s_ = file_str(f);
    for (char * l = strtok(s_, "\n"); l != NULL; l = strtok(NULL, "\n")) {
        Token t;

        if (strstr(l, "#define") != NULL) {
            Animal custom = customizeAnimal(l);
            animals.push_back(custom);

        } else {
            vector<Token> token = t.tokenize(l, animals);
            tokens_to_asm(token, i);
            i++;
        }
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