#include <string>
#include <vector>
#include "Sommet.hpp"
#include "Vehicule.hpp"

#ifndef DEF_GRAPHE
#define DEF_GRAPHE

class Graphe
{
private:

    std::vector<Sommet *> listeSommet;
	std::vector<std::vector<int>> matriceAdj;
	

public:
    Graphe(std::vector<Sommet *> sommet);
    ~Graphe();
    std::vector<Sommet *> getSommets();
    
    void genererMatrice(std::string listeArc);
    Sommet *trouverSommet(std::string id); 
    void lireGraphe();
    Graphe extractionGraphe(Vehicule voiture);
    void plusCourtChemin(std::string depart, std::string arrivee, Vehicule *voiture);
};
#endif