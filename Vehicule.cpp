#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule()
{}

//constructeur de la classe Vehicule
Vehicule::Vehicule(std::string carbu, int autonomie, int coeff):typeCarburant{carbu}, autonomieMax{autonomie}, autonomieRestante{autonomie}, consommation{coeff}
{
}

//met à jour l'autonomie du véhicule avec la distance parcourue donnée en arguments
void Vehicule::rouler(int distanceParcourue)
{
    autonomieRestante = autonomieRestante - distanceParcourue*consommation;
    if (autonomieRestante < 0)
    {
        autonomieRestante = 0;
    }
}

//remet l'autonomie du véhicule au maximum
void Vehicule::faire_plein()
{
    autonomieRestante = 100;
}

//retourne l'autonomie restante du véhicule
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

//renvoit true si le véhicule peut se recharger au type de pompe passé en paramètre
bool Vehicule::plein(string type){
    if (type == "hybrid" || (type != "rien" && typeCarburant == "hybrid"))
        return true;
    return type == typeCarburant;

}