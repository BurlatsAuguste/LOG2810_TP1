#ifndef DEF_GRAPHE
#define DEF_GRAPHE
#endif

#include <string>
#include <vector>
#include "Arc.hpp"
#include "Vehicule.hpp"

class Graphe
{
private:

    std::vector<Sommet> liste_sommet;
    std::vector<Arc> liste_arc;
    //Nous devrions créer un parametre nommé Graphe

public:
    Graphe(std::vector<Sommet> sommet,std::vector<Arc> arc);
    ~Graphe();
    void creerGraphe(std::string file_name);
    void lireGraphe();
    Graphe extractionGraphe(Vehicule voiture);
    void plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture);

};
