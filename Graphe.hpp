#include <string>
#include <vector>
#include <set>
#include <list>
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
    Graphe();
    ~Graphe();
    std::vector<Sommet *> getSommets();
    
    void genererMatrice(std::string listeArc);
    Sommet *trouverSommet(std::string id);
    void lireGraphe();

    void ajouterSommet(Sommet* sommet);
    void ajouterArc(int i, int j, int distance);
    void ajouterArc(std::string id1, std::string id2, int distance);

    std::vector<int> plusLong(std::set<Sommet*> visites, Sommet* depart, int restant, int consommation);

    int autonomieRestante(Vehicule voiture, std::vector<Sommet *> chemin);
    Graphe extractionGraphe(Vehicule voiture, Sommet* depart);
    void plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture);
};
#endif