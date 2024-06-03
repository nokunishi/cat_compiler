#include "asm.h"

string normal(const string&name) {
    string name_ = "";
    name_ = toupper(name[0]);

    for (int i = 1; i < name.length(); i++) {
        name_ += name[i];
    }
    return name_;
}

string demand(const string&name) {
    string name_ = "";
    name_ = toupper(name[0]);

    for (int i = 1; i < name.length(); i++) {
        name_ += toupper(name[i]);
    }
    return name_;
}

void create_asm(const string &p, const string animal, const string str, int l_no) {
    string line = "";
    ifstream f(p);
    ofstream out;

    out.open("../out/" + animal + ".s", std::ios_base::app|ios::binary);
    ifstream out_("../out/" + animal + ".s");

    string no = to_string(l_no);

    if (out_.peek() == std::ifstream::traits_type::eof()) {
        while (line.find("input@PAGE") == string::npos) {
            out << line << endl;
            getline(f, line);
        }

        out << "    adrp x1,input" + no + "@PAGE" << endl;
        out << "    add x1, x1,input" + no + "@PAGEOFF" << endl;
        getline(f, line);
        getline(f, line);

        while (line.find("input:") == string::npos) {
            out << line << endl;
            getline(f, line);
        }
        out << "input" + no + ": .ascii \"" + str + " \\n\"" << endl;
    } else {
        out << "input" + no + ": .ascii \"" + str + " \\n\"" << endl;
    }
}


void tokens_to_asm(const vector<Token> &tokens, int i) {

    if (tokens[ANIMAL_IDX].type != Token::TokenType::animal || 
        tokens[ACTION_IDX].type != Token::TokenType::action || 
            tokens[SEP_IDX].type != Token::TokenType::sep) {
                cout << tokens[ANIMAL_IDX].value << endl;
        return;
    }

    string str;
    if (tokens[SEP_IDX].value == ".") {
        str = normal(tokens[STR_IDX].value);
    }
    if (tokens[SEP_IDX].value == "!") {
        str = normal(tokens[STR_IDX].value) + "!";
    }
    if (tokens[SEP_IDX].value == "!!") {
        str = demand(tokens[STR_IDX].value) + "!!";
    }
    create_asm("model.s", tokens[ANIMAL_IDX].value, str, i);
}