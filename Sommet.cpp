#include <string>
#include <vector>
#include "Sommet.hpp"

using namespace std;

//constructeur de la classe Sommet
Sommet::Sommet(string id, string recharge, int indi):identifiant{id},type{recharge},indice{indi}
{
    
}

//retourne l'identifiant du sommet
string Sommet::getId(){
    return identifiant;
}

//retourne le type de carburant du sommet
string Sommet::getType(){
    return type;
}

//retourne l'indice du sommet
int Sommet::getIndice()
{
    return indice;
}