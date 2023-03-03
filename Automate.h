#pragma once
#include <stack>
#include "symbole.h"
#include "lexer.h"
#define AUTOMATE_H
using namespace std;

class Etat;


class Automate {

    public:
        Automate(string flux);

        void decalage(Symbole * s, Etat * e);

        void reduction(int n,Symbole * s);

        void run();

        void popAndDestroySymbol();

        Entier * popSymbol();

    protected:
        Lexer * lex;
        deque <Etat *> pileEtat;
        deque <Symbole *> pileSymbole;

};