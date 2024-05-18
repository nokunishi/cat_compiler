#ifndef ASM
#define ASM

#include <iostream>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

using namespace std;

string exclaim(const string&name);
string demand(const string&name);
void create_asm(const string &p, const string &str, int lno);

#endif