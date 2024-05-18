#include "token.h"

Token::Token() {
    value = "";
}

Token::Token(TokenType t, string v) {
    type = t;
    value =v;
}


int Token::parseStr(vector<Token> &tokens, const string&str, int i) {
    string buf = "";
    char c = str[i];

    while (i < str.length() -1) {
        buf.push_back(c);
        i++;
        c = str[i];
    }
    tokens.push_back(Token(TokenType::str, buf));
    if (buf.length() > 0) {
        return i + 1;
    } else {
        exit(EXIT_FAILURE);
    }
}

int Token::parseSep(vector<Token> &tokens, const string&str, int i) {
    char c = str[i];

    if (c == '.') {
        tokens.push_back(Token(TokenType::sep, "."));
        return i + 1;
    }
    else if (c == '!' && str[i+1] == '(') {
        tokens.push_back(Token(TokenType::sep, "!"));
        return i + 1;
    }
    else if (c == '!' && str[i+1] == '!') {
        tokens.push_back(Token(TokenType::sep, "!!"));
        return i + 2;
    }

    exit(EXIT_FAILURE);
}

int Token::parseAnimal(vector<Token> &tokens, const string&str, int i) {
    char c = str[i];
    string buf;

    while (isalpha(c)) {
        buf.push_back(c);
        i++;
        c = str[i];
    }

    if (buf == "meow") {
        tokens.push_back(Token(TokenType::animal, "cat"));
    }
    if (buf == "woof") {
        tokens.push_back(Token(TokenType::animal, "dog"));
    }

    if (tokens.size() != 1) {
        exit(EXIT_FAILURE);
    }

    tokens.push_back(Token(TokenType::action, "printf"));
    return i;
}


vector<Token> Token::tokenize(const string &str) {
    vector<Token> tokens;
    string buf;
    int i = 0;
    char c = str[i];

    
    i = parseAnimal(tokens, str, i);
    i = parseSep(tokens, str, i);

    c = str[i];
    if (c != '(') {
        exit(EXIT_FAILURE);
    }

    i = parseStr(tokens, str, i+1);

    return tokens;
}
