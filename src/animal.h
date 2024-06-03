#ifndef ANIMAL
#define ANIMAL


#include <iostream>
using namespace std;

class Animal {
    public:
    string type;
    string sound;

    Animal(string, string);
};

Animal customizeAnimal(char * l);


#endif 