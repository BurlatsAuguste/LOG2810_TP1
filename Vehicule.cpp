#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule()
{}

Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, autonomieMax{autonomie}, autonomieRestante{autonomie}, consommation{coeff}
{
}

void Vehicule::rouler(int distanceParcourue)
{
    autonomieRestante = autonomieRestante - distanceParcourue*consommation;
    if (autonomieRestante < 0)
    {
        autonomieRestante = 0;
    }
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
    if (type == "hybrid" || (type != "rien" && typeCarburant == "hybrid"))
        return true;
    return type == typeCarburant;

}