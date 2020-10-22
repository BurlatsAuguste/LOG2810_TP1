#ifndef DEF_ARC
#define DEF_ARC

#include "Sommet.h"

class Arc
{
private:
    int distance;
    Sommet debut;
    Sommet arrivee;

public:
    Arc(Sommet d, Sommet a, int taille);
    ~Arc();
};
