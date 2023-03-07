#include <iostream>
#include "Automate.h"


int main(void) {
   string chaine;

   cout << "Entrez l'expression arithmétique à évaluer :" << endl;
   cin >> chaine;

   Automate * analyseur = new Automate(chaine);
   analyseur->run();

   return 0;
}