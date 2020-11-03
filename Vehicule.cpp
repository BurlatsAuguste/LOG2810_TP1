#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule()
{

}
Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, autonomieMax{autonomie}, autonomieRestante{autonomie},consommation{coeff}
{
}

void Vehicule::majAutonomie(int newAutonomie)
{
    autonomieRestante = newAutonomie;
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

string Vehicule::getCarbu()
{
    return typeCarburant;
}