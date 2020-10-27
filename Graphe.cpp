#include "Graphe.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Graphe::Graphe(vector<Sommet *> sommet):listeSommet{sommet}
{
	int size = sommet.size();
	for (int i = 0; i < size; i++)
    {
		matriceAdj.push_back(vector<int>());
		for (int j = 0; j < size; j++)
        {
			matriceAdj[i].push_back(0);
		}
	}
}

Graphe::~Graphe()
{
    for(int i = 0; i < int(listeSommet.size()); i++)
    {
        delete(listeSommet[i]);
    }
}

//affiche le graphe
//pour chaque noeud affiche le noeud et ses voisins
//j'ai assumé que les voisins n'était que ceux où on pouvait aller depuis le noeud en question
//ceux qui permettent de rejoindre le noeud ne sont pas considérés comme voisins
void Graphe::lireGraphe()
{
    for(int i = 0; i < int(listeSommet.size()); i++)
    {
        cout << "(" << listeSommet[i]->getId() <<", " <<listeSommet[i]->getType() <<", (";
		for (int j = 0; j < int(listeSommet.size()); j++)
        {

            if (matriceAdj[i][j] != 0)
            {
                cout << listeSommet[j]->getId() <<", ";
			}

        }
        cout << ")" <<endl;
    }
}

vector<Sommet *> Graphe::getSommets()
{
    return listeSommet;
}

Sommet *Graphe::trouverSommet(string id){
    for(int i = 0; i<int(listeSommet.size());i++){
        if(listeSommet[i]->getId() == id){
            return listeSommet[i];
        }
    }
    return nullptr;
}

void Graphe::genererMatrice(std::string listeArc){
    string delimiter = ";";
    size_t pos;
    string token;
    Sommet *depart;
    Sommet * arrivee;
    int distance;
    //on découpe la string au niveau des ; et on génere un arc à l'aide de chaque morceau
    while((pos = listeArc.find(delimiter)) != string::npos){
        token = listeArc.substr(0, pos);
        listeArc.erase(0, pos + delimiter.length());

        depart = trouverSommet(token.substr(0, token.find(',')));
        token.erase(0, token.find(',')+1);

        arrivee = trouverSommet(token.substr(0, token.find(',')));
        token.erase(0, token.find(',')+1);

        distance = stoi(token);
        matriceAdj[depart->getIndice()][arrivee->getIndice()] = distance;
    }

}
