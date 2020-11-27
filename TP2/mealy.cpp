#include "mealy.hpp"

using namespace std;

mealy::mealy(int identifiant, char l):id{identifiant}, lettre{l}
{}

mealy::~mealy()
{
    delete(suivant);
}

void mealy::ajoutSuivant(mealy *etat)
{
    suivant = etat;
}


int mealy::compteErreur(std::string mot, int indice)
{
    if(indice == int(mot.size()))
        return 0;

    if(lettre == mot.at(indice))
        return 0 + suivant->compteErreur(mot, indice+1);
    else
        return 1 + suivant->compteErreur(mot, indice+1);
}