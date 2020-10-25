#include "Graphe.hpp"
#include <string>

using namespace std;

Graphe::Graphe(vector<Sommet> sommet,vector<Arc> arc):listeSommet{sommet},listeArc{arc}
{

}

vector<Sommet> Graphe::getSommets()
{
    return this->listeSommet;
}

vector<Arc> Graphe::getArcs()
{
    return this->listeArc;
}

void Graphe::updateDegre(){
    int degreEntrant;
    int degreSortant;
    for(int i = 0; i < int(this->listeSommet.size()); i++)
    {
        degreEntrant = 0;
        degreSortant = 0;

        for(int j = 0; j < int(this->listeArc.size()); j++)
        {
            if(this->listeArc[j].getDebut()->getId() == this->listeSommet[i].getId()){
                degreEntrant++;
            }
            if(this->listeArc[j].getArrivee()->getId() == this->listeSommet[i].getId()){
                degreSortant++;
            }
        }
        this->listeSommet[i].updateDegre(degreSortant + degreEntrant);
    }
}
