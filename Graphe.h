#ifndef DEF_GRAPHE
#define DEF_GRAPHE
#endif

#include <string>
#include "Arc.h"
#include "Vehicule.h"

class Graphe
{
private:

    Sommet *liste_sommet;
    Arc *liste_arc;
    //Nous devrions créer un parametre nommé Graphe

public:
    Graphe(Sommet* sommet,Arc* arc);
    ~Graphe();
    void creerGraphe(std::string file_name);
    void lireGraphe();
    Graphe extractionGraphe(Vehicule voiture);
    void plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture);

};
