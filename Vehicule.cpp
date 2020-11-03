#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule()
{

}
//constructeur de véhicule
Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, autonomieMax{autonomie}, autonomieRestante{autonomie},consommation{coeff}
{
}

//change la valeur de l'autonomie restante par celle donnée en argument
void Vehicule::majAutonomie(int newAutonomie)
{
    autonomieRestante = newAutonomie;
}

//retourne l'autonomie du véhicule
int Vehicule::getAutonomie() {
    return autonomieRestante;
}

//retourne l'autonomie maximale du véhicule
int Vehicule::getAutonomieMax() {
    return autonomieMax;
}

//retourne la consommation du véhicule
int Vehicule::getConso()
{
    return consommation;
}

//retourne le type de carburant du véhicule
string Vehicule::getCarbu()
{
    return typeCarburant;
}