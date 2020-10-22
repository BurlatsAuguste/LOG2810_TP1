#include "Arc.h"
#include <string>
using namespace std;

Arc::Arc(Sommet *d, Sommet *a, int taille):debut{d},arrivee{a},distance{taille}
{
}

Sommet* Arc::getArrivee(){
    return arrivee;
}
Sommet* Arc::getDebut(){
    return debut;
}
int Arc::getDistance(){
    return distance;
}
