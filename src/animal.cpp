#include "animal.h"

Animal::Animal(string t, string s) {
    type = t;
    sound = s;
}


Animal customizeAnimal(char * l) {
    char tmp[100];
    strcpy(tmp, l);
    int i = 8;

    string type = "";
    string sound = "";

    while (i < sizeof(tmp) && tmp[i] != ' ') {
        type.push_back(tmp[i]);
        i++;
    }

    if (!isspace(tmp[i])) {
        throw "invalid format";
    }
    i++;
    while (i < sizeof(tmp) && isalpha(tmp[i])) {
        sound.push_back(tmp[i]);
        i++;
    }
    return Animal(type, sound);
}