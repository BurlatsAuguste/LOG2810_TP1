#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule() : typeCarburant{ "essence" }, autonomieRestante{ 10 }, autonomieMax{ 10 }, consommation{ 1 }
{

}
Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, consommation{coeff}, autonomieRestante{autonomie}, autonomieMax{autonomie}
{
}

void Vehicule::rouler(int distanceParcourue)
{
    autonomieRestante = autonomieRestante - distanceParcourue*consommation;
}

void Vehicule::faire_plein()
{
    autonomieRestante = 100;
}

int Vehicule::getAutonomie() {
    return autonomieRestante;
}

int Vehicule::getAutonomieMax() {
    return autonomieMax;
}

int Vehicule::getConso()
{
    return consommation;
}

bool Vehicule::plein(string type){
    if (type.compare("hybrid") == 0)
        return true;
    return type.compare(typeCarburant)==0;

}
