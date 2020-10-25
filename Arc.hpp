#include "Sommet.hpp"

#ifndef DEF_ARC
#define DEF_ARC



class Arc
{
private:
    int distance;
    Sommet *debut;
    Sommet *arrivee;

public:
    Arc(Sommet *d, Sommet *a, int taille);
    int getDistance();
    Sommet* getDebut();
    Sommet* getArrivee();
};
#endif