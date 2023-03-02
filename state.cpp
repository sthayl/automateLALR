#include "Etat.h"
#include "state.h"

bool E0::transition(Automate & automate, Symbole * s){
    switch (*s){
    case INT:
        automate.decalage(s, new E3);
        break;
    case OPENPAR:
        automate.decalage(s, new E2);
        break;
    case EXPR:
        automate.decalage(s, new E1);
    }
    return false;
}

bool E1::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
        automate.decalage(s, new E4);
        break;
    case MULT:
        automate.decalage(s, new E5);
        break;
    case FIN:
    //accepter
        Expr * e = new Expr(s->getValeur());
        automate.reduction(1,e);
        break;
    }
    return false;
}

bool E2::transition(Automate & automate, Symbole * s){
    switch (*s){
    case INT:
        automate.decalage(s, new E3);
        break;
    case OPENPAR:
        automate.decalage(s, new E2);
        break;
    case EXPR:
        automate.decalage(s, new E6);
    }
    return false;
}

bool E3::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
    case OPENPAR:
        //r5 : E -> val
        Entier *s1 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur());
        automate.reduction(1,e);
        break;
    }
    return false;
}

bool E4::transition(Automate & automate, Symbole * s){
    switch (*s){
    case INT:
        automate.decalage(s, new E3);
        break;
    case OPENPAR:
        automate.decalage(s, new E2);
        break;
    case EXPR:
        automate.decalage(s, new E7);
    }
    return false;
}

bool E5::transition(Automate & automate, Symbole * s){
    switch (*s){
    case INT:
        automate.decalage(s, new E3);
        break;
    case OPENPAR:
        automate.decalage(s, new E2);
        break;
    case EXPR:
        automate.decalage(s, new E8);
    }
    return false;
}

bool E6::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
        automate.decalage(s, new E4);
        break;
    case MULT:
        automate.decalage(s, new E5);
        break;
    case CLOSEPAR:
        automate.decalage(s, new E9);
        break;
    }
    return false;
}

bool E7::transition(Automate & automate, Symbole * s){
    switch (*s){
    case MULT:
        automate.decalage(s, new E5);
        break;
    case PLUS:
    case CLOSEPAR:
    case FIN:
    //règle 2 : E -> E+E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()+s2->getValeur());
        automate.reduction(3,e);
        break;
    }
    return false;
}

bool E8::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
    //règle 3 : E -> E+E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()*s2->getValeur());
        automate.reduction(3,e);
        break;
    }
    return false;
}

bool E9::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        automate.popAndDestroySymbol();
        Expr * s1 = (Expr*) automate.popSymbol();
        automate.popAndDestroySymbol();
        automate.reduction(3,s1);
        break;
    }
    return false;
}

