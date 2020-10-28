#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule()
{

}
Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, consommation{coeff}, autonomieRestante{autonomie}, autonomieMax{autonomie}
{
}

void Vehicule::rouler(int distanceParcourue)
{
    autonomieRestante = autonomieRestante - distanceParcourue*consommation;
}

void Vehicule::fairePlein(string carburant)
{
    if(carburant != "rien" && (carburant == "hybrid" || typeCarburant =="hybrid" || typeCarburant == carburant))
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