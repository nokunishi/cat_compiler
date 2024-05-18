#include "asm.h"

string exclaim(const string&name) {
    string name_ = "";
    name_ = toupper(name[0]);

    for (int i = 1; i < name.length(); i++) {
        name_ += name[i];
    }
    name_ += "!";
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

void create_asm(const string &p, const string &str, int lno) {
    string line = "";
    ifstream f(p);
    ofstream out;
    
    stringstream ss;
    ss << lno;
    string name = ss.str();

    out.open("../output/" + name + ".s", ios::out|ios::binary);

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