#include "Arc.h"
#include <string>
using namespace std;

Arc::Arc(Sommet *d, Sommet *a, int taille)
{
    distance = taille;
    debut = d;
    arrivee = a;
}