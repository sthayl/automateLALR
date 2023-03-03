#pragma once
#include <string>
#include <iostream>
#include "symbole.h"
#include "Automate.h"
using namespace std;

class Etat {
    public:
        Etat();
        Etat(string stateName) : name(stateName){};
        virtual ~Etat(){};
        void print() const;
        virtual bool transition(Automate & automate, Symbole * s) = 0;
        void print(){cout << name;}

    protected:
        string name;
};
