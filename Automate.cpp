#include <iostream>
#include "state.h"
using namespace std;

Automate::Automate(string flux){
    this->lex = new Lexer(flux);
    E0 * depart = new E0();
    pileEtat.push_back(depart);
}

void Automate::run(){

    bool syntaxeValide = true;
    int res = 0;
    Symbole * s;
    while(syntaxeValide){
        if(*s != FIN){
            s = lex->Consulter();
            lex->Avancer();
        }

        //--Affichage debug--
        s->Affiche();
        cout<<endl;
        pileEtat.back()->print();
        cout << endl;
        //-------------------

        syntaxeValide = pileEtat.back()->transition(*this, s);

        //--Affichage debug--
        cout << syntaxeValide << endl;
        cout << "----------------" << endl;
        //-------------------
    }
    res = pileSymbole.front()->getValeur();
    cout << "Res = " << res << endl;
    if(*pileSymbole.back() == ERREUR) {
        cout << "Syntaxe incorrecte" << endl;
    }
    else{
        int res = pileSymbole.front()->getValeur();
        cout << "Résultat : " << res << endl;
    }
}

void Automate::decalage(Symbole * s, Etat * e) {

    //--Affichage debug--
    // cout << "Passage de l'état ";
    // pileEtat.back()->print();
    // cout << " à l'état ";
    // e->print();
    // cout << endl;
    //-------------------
    
    pileSymbole.push_back(s);
    pileEtat.push_back(e);
    // if (s->isTerminal()) {
    //     lex->Avancer();
    // }
}

void Automate::reduction(int n,Symbole * s) {
    for (int i=0;i<n;i++){
        delete(pileEtat.back());
        pileEtat.pop_back();
    }
    pileEtat.back()->transition(*this,s);
    lex->Reculer();
}

void Automate::popAndDestroySymbol(){
    delete(pileSymbole.back());
    pileSymbole.pop_back();
}

Entier * Automate::popSymbol(){
    Entier * ret = (Entier *) pileSymbole.back();
    pileSymbole.pop_back();
    return ret;
}
