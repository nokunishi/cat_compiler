#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

using namespace std;

enum class TokenType {
    _print,
    _str,
    sep,
};

struct Token {
    TokenType type;
    string value;

    Token(TokenType t, string v) {
        type = t;
        value =v;
    }
};

void customize(const string &p, const string &str) {
    string line = "";
    ifstream f(p);
    ofstream out;
    out.open("../output/out.s",ios::out|ios::binary);

    while (line.find("mov x2,") == string::npos) {
        out << line << endl;
        getline(f, line);
    }

    out << "    mov x2, " + to_string(str.length() + 1) << endl;

    while (line.find("input:") == string::npos) {
        out << line << endl;
        getline(f, line);
    }

    out << "input: .ascii \"" + str + "\"" << endl;
}



string tokens_to_asm(const vector<Token> &tokens) {
    stringstream output;

    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];

        if (token.type == TokenType::_print) {
            if (i + 1 < tokens.size() && tokens.at(i+1).type == TokenType::_str) {
                if (i + 2 < tokens.size() && tokens.at(i+2).type == TokenType::sep) {
                    customize("model.s", tokens[i+1].value);
                }
            }
        }

    }

    return "";
}

int returnVal(vector<Token> &tokens, const string&str, int i) {
    string buf = "";
    char c = str[i];

    while (c != ')') {
        buf.push_back(c);
        i++;
        c = str[i];
    }

    tokens.push_back(Token(TokenType::_str, buf));
    if (buf.length() > 0) {
        return i + 1;
    } else {
        exit(EXIT_FAILURE);
    }
}


vector<Token> tokenize(const string &str) {
    vector<Token> tokens;
    string buf;
    int i = 0;
    char c = str[i];

    while (isalpha(c)) {
        buf.push_back(c);
        i++;
        c = str[i];
    }

    if (buf == "meow") {
        tokens.push_back(Token(TokenType::_print, "printf"));
        buf.clear();
    }

    if (c != '(') {
        exit(EXIT_FAILURE);
    }

    i = returnVal(tokens, str, i+1);
    c = str[i];

    if (c == '.') {
        tokens.push_back(Token(TokenType::sep, "."));
    }

    return tokens;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "invalid num of args" << endl;
        return EXIT_FAILURE;
    }

    
    fstream f(argv[1]);
    stringstream s;
    string contents;

    s << f.rdbuf();
    vector<Token> token = tokenize(s.str());
    tokens_to_asm(token);

    return EXIT_SUCCESS;
}