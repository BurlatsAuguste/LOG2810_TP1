#include <string>
#include <vector>
#include "Sommet.hpp"

using namespace std;

Sommet::Sommet(string id, string recharge, int indi):identifiant{id},type{recharge},indice{indi}
{
    
}


string Sommet::getId(){
    return identifiant;
}

string Sommet::getType(){
    return type;
}

int Sommet::getIndice()
{
    return indice;
}