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

void printf_asm(ofstream &out, const string str, string l_no) {
    string len = to_string(str.length() + 2);

    out << "    mov x0, #1" << endl;        
    out << "    adrp x1,input" + l_no + "@PAGE" << endl;
    out << "    add x1, x1,input" + l_no + "@PAGEOFF" << endl;
    out << "    mov x2, #" + len << endl;
    out << "    mov x16, #4" << endl;     
    out << "    svc #0x80" << endl;
    out << "\n" << endl;
}

void create_asm(vector<string> &data, string animal, const string str, int l_no) {
    ofstream out;
    out.open("../out/" + animal + ".s", std::ios_base::app|ios::binary);
    ifstream out_("../out/" + animal + ".s");

    if (out_.peek() == std::ifstream::traits_type::eof()) {
        out << ".global _start" << endl;
        out << ".align 2" << endl;
        out << "\n" << endl;
        out << "_start:" << endl;
    }

    printf_asm(out, str, to_string(l_no));

    data.push_back("input" + to_string(l_no) + ": .ascii \"" + str + " \\n\"");
    out.close();
}


void tokens_to_asm(const vector<Token> &tokens, unordered_map<string, vector<string>> &m, int i) {

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
    string animal = tokens[ANIMAL_IDX].value;

    create_asm(m[animal], animal, str, i);
}