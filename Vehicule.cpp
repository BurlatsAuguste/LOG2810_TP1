#include "Vehicule.hpp"
#include <string>

using namespace std;

Vehicule::Vehicule(std::string carbu, int autonomie_max, int autonomie_depart, int taux)
{
	this->taux = taux;
	type_carburant = carbu;
    autonomie_maximale = autonomie_max;
    autonomie = autonomie_depart;
}

void Vehicule::rouler(int distance_parcourue)
{
    autonomie = autonomie-distance_parcourue*taux;
}

void Vehicule::faire_plein()
{
    autonomie = autonomie_maximale;
}

int Vehicule::getAutonomie() {
    return autonomie;
}