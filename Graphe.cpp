#include "Graphe.hpp"
#include <string>
#include <iostream>

using namespace std;

Graphe::Graphe(vector<Sommet> sommet,vector<Arc> arc):listeSommet{sommet},listeArc{arc}
{

}

//affiche le graphe
//pour chaque noeud affiche le noeud et ses voisins
//j'ai assumé que les voisins n'était que ceux où on pouvait aller depuis le noeud en question
//ceux qui permettent de rejoindre le noeud ne sont pas considérés comme voisins
void Graphe::lireGraphe()
{
    for(int i = 0; i < int(this->listeSommet.size()); i++)
    {
        vector<Sommet *> voisins;
        for(int j = 0; j < int(this->listeArc.size());j++)
        {
            if(this->listeArc[j].getDebut()->getId() == this->listeSommet[i].getId())
            {
                voisins.push_back(this->listeArc[j].getArrivee());
            }
        }
        cout << "(" << this->listeSommet[i].getId() <<", " <<this->listeSommet[i].getType() <<", (";
        for(int j = 0; j < int(voisins.size()); j++)
        {
            cout << voisins[j]->getId() <<", ";
        }
        cout << ")" <<endl;
        voisins.clear();
    }
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
