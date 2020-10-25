#include <string>
#include "Sommet.hpp"

using namespace std;

Sommet::Sommet(string id, string recharge):identifiant{id},type{recharge},degre{0}
{
    
}

Sommet::~Sommet(){
    
}

int Sommet::getDegre(){
    return degre;
}

void Sommet::update_degre(int deg){

    degre=deg;
}

std::string Sommet::getId(){
    return identifiant;
}

std::string Sommet::getType(){
    return type;
}