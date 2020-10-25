#include <string>
#include <vector>
#include "Arc.hpp"
#include "Sommet.hpp"
#include "Vehicule.hpp"

#ifndef DEF_GRAPHE
#define DEF_GRAPHE




class Graphe
{
private:

    std::vector<Sommet> listeSommet;
    std::vector<Arc> listeArc;
    //Nous devrions créer un parametre nommé Graphe

public:
    Graphe(std::vector<Sommet> sommet,std::vector<Arc> arc);
    std::vector<Sommet> getSommets();
    std::vector<Arc> getArcs();
    void creerGraphe(std::string filename);
    void lireGraphe();
    Graphe extractionGraphe(Vehicule voiture);
    void plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture);
    void updateDegre();
};
#endif