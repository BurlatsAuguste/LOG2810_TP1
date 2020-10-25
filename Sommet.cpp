#include <string>
#include <vector>
#include "Sommet.hpp"

using namespace std;

Sommet::Sommet(string id, string recharge):identifiant{id},type{recharge},degre{0}
{
    
}

int Sommet::getDegre(){
    return degre;
}

void Sommet::updateDegre(int deg){
    this->degre=deg;
}

string Sommet::getId(){
    return identifiant;
}

string Sommet::getType(){
    return type;
}

vector<Sommet *> Sommet::getVoisins()
{
    return voisins;
}

void Sommet::updateVoisins(vector<Sommet *> voisinage){
    this->voisins = voisinage;
}