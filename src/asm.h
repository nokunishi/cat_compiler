#ifndef ASM
#define ASM

#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>
#include "token.h"

using namespace std;

string normal(const string&name);
string demand(const string&name);
void create_asm(vector<string>&,const string, const string, int);
void tokens_to_asm(const vector<Token> &tokens,unordered_map<string, vector<string>> &, int);
void printf_asm(ofstream&, string str, string l_no);

#endif