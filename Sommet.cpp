#include <string>
#include <vector>
#include "Sommet.hpp"

using namespace std;

Sommet::Sommet(string id, string recharge, int indi):identifiant{id},type{recharge},indice{indi}
{
    
}
bool Sommet::estPompe(string typeCarbu)
{
    if(type == "hybrid" || (typeCarbu =="hybrid" && type !="rien") || typeCarbu == type)
        return true;
    else
        return false;
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