#pragma once

#include <string>
#include <map>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, EXPR, ERREUR };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "EXPR", "ERREUR" };

class Symbole {
   public:
      Symbole(int i, bool isTer) : ident(i) { terminal = isTer; }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();
      bool isTerminal() {return terminal;}
      virtual int getValeur(){return 0;}

   protected:
      bool terminal;
      int ident;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT, true), valeur(v) { }
      ~Entier() {};
      virtual void Affiche();
      int getValeur() {return valeur;}
   protected:
      int valeur;
};

class Expr : public Symbole {
   public:
      Expr(int v) : Symbole(EXPR, false) {valeur = v;}
      ~Expr() {}
      int getValeur() {return valeur;}
      
   protected:
      int valeur;
};
