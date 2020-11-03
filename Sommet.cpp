#include <string>
#include <vector>
#include "Sommet.hpp"

using namespace std;

Sommet::Sommet(string id, string recharge, int indi):identifiant{id},type{recharge},indice{indi}
{
    
}

//retourne vrai si la pompe est compatible avec le type de carburant donné en argumant
//retourne faux sinon
bool Sommet::estPompe(string typeCarbu)
{
    if(type == "hybrid" || (typeCarbu =="hybrid" && type !="rien") || typeCarbu == type)
        return true;
    else
        return false;
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