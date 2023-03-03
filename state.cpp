#include "state.h"
#include "symbole.h"

E0::E0() : Etat("E0"){};
E1::E1() : Etat("E1"){};
E2::E2() : Etat("E2"){};
E3::E3() : Etat("E3"){};
E4::E4() : Etat("E4"){};
E5::E5() : Etat("E5"){};
E6::E6() : Etat("E6"){};
E7::E7() : Etat("E7"){};
E8::E8() : Etat("E8"){};
E9::E9() : Etat("E9"){};

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
        break;
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
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
    {
        //accepter
        Expr * e = new Expr(s->getValeur());
        automate.reduction(1,e);
        return false;
    }
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
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
        break;
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
}

bool E3::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    {
        //r5 : E -> val
        Entier *s1 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur());
        automate.reduction(1,e);
        break;
    }
    case FIN:
    {
        //r5 : E -> val
        Entier *s1 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur());
        automate.reduction(1,e);
        break;
        //return false;
    }
    
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
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
        break;
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
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
        break;
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
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
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
}

bool E7::transition(Automate & automate, Symbole * s){
    switch (*s){
    case MULT:
        automate.decalage(s, new E5);
        break;
    case PLUS:
    case CLOSEPAR:
    {
    //règle 2 : E -> E+E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()+s2->getValeur());
        automate.reduction(3,e);
        break;
    }
    case FIN:
    {
    //règle 2 : E -> E+E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()+s2->getValeur());
        automate.reduction(3,e);
        return false;
    }
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
}

bool E8::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    {
    //règle 3 : E -> E+E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()*s2->getValeur());
        automate.reduction(3,e);
        break;
    }
    case FIN:
    {
    //règle 3 : E -> E*E
        Entier *s1 = (Entier *) automate.popSymbol();
        automate.popAndDestroySymbol();
        Entier *s2 = (Entier *) automate.popSymbol();
        Expr * e = new Expr(s1->getValeur()*s2->getValeur());
        automate.reduction(3,e);
        //return false;
        break;
    }
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
}

bool E9::transition(Automate & automate, Symbole * s){
    switch (*s){
    case PLUS:
    case MULT:
    case CLOSEPAR:
    {
        automate.popAndDestroySymbol();
        Expr * s1 = (Expr*) automate.popSymbol();
        automate.popAndDestroySymbol();
        automate.reduction(3,s1);
        break;
    }
    case FIN:
    {
        automate.popAndDestroySymbol();
        Expr * s1 = (Expr*) automate.popSymbol();
        automate.popAndDestroySymbol();
        automate.reduction(3,s1);
        return false;
    }
    default:
        automate.decalage(new Symbole(ERREUR, false), NULL);
        return false;
    }
    return true;
}

