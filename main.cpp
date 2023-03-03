#include <iostream>
#include "Automate.h"


int main(void) {
   string chaine("(34+1)*123");

   Automate * analyseur = new Automate(chaine);
   analyseur->run();

   // Lexer l(chaine);

   // Symbole * s;
   // while(*(s=l.Consulter())!=FIN) {
   //    s->Affiche();
   //    cout<<endl;
   //    l.Avancer();
   // }
   return 0;
}