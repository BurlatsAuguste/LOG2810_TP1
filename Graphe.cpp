#include "Graphe.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <climits>

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

Graphe::Graphe()
{}

Graphe::~Graphe()
{}

void Graphe::deleteSommet()
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
    for (int i = 0; i < int(listeSommet.size()); i++)
    {
        cout << "(" << listeSommet[i]->getId() << ", " << listeSommet[i]->getType() << ", (";
        for (int j = 0; j < int(listeSommet.size()); j++)
        {

            if (matriceAdj[i][j] != 0 || matriceAdj[j][i] != 0)
            {
                cout << listeSommet[j]->getId() << ", ";
            }

        }
        cout << ")" << endl;
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

void Graphe::genererMatrice(string listeArc){
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

void Graphe::ajouterSommet(Sommet* sommet)
{
    int i = int(listeSommet.size());
    Sommet* nouveau = new Sommet(sommet->getId(), sommet->getType(), i);
    listeSommet.push_back(nouveau);
    matriceAdj.push_back(vector<int>());
    matriceAdj[i].push_back(0);
    for (int j = 0; j < int(listeSommet.size()); j++)
    {
        matriceAdj[j].push_back(0);
        matriceAdj[i].push_back(0);
    }
}


void Graphe::ajouterArc(int i, int j, int distance)
{
    matriceAdj[i][j] = distance;
}

void Graphe::ajouterArc(string id1, string id2, int distance)
{
    int i = trouverSommet(id1)->getIndice();
    int j = trouverSommet(id2)->getIndice();
    ajouterArc(i, j, distance);
}


bool contains(vector<Sommet*> v, int i)
{
    for (Sommet* s : v)
    {
        if (s->getIndice() == i)
            return true;
    }
    return false;
}

vector<int> Graphe::plusLong(set<Sommet*> visites, Sommet* depart, int restant, int consommation)
{
    int i = depart->getIndice();

    int max = 0;
    vector<int> trajet;
    bool end = true;


    for (int arc = 0; arc < int(listeSommet.size()); arc++)
    {
        if (matriceAdj[i][arc] != 0 && matriceAdj[i][arc]*consommation<=restant && visites.count(listeSommet[arc]) == 0)
        {
            set<Sommet*> copie = visites;
            copie.insert(listeSommet[arc]);
            vector<int> chemin = plusLong(copie, listeSommet[arc], restant - matriceAdj[i][arc]*consommation, consommation);
            int distance = chemin[0]+matriceAdj[i][arc];
            if (distance > max)
            {
                max = distance;
                chemin.push_back(depart->getIndice());
                chemin[0] = distance;
                trajet = chemin;
            }
            end = false;
        }
    }
    if (end)
    {
        trajet.push_back(0);
        trajet.push_back(i);
    }
    return trajet;
}

Graphe Graphe::extractionGraphe(Vehicule v, Sommet* depart)
{
    set<Sommet*> visites;
    visites.insert(depart);
    vector<int> trajet = plusLong(visites, depart, v.getAutonomieMax(), v.getConso());

    int distance = trajet[0];

    Graphe nouveau;
    
    for (int i=trajet.size()-1; i > 0 ; i--)
    {
        nouveau.ajouterSommet(listeSommet[trajet[i]]);
        if (i - 1 >= 1)
        {
            nouveau.ajouterArc(int(trajet.size()) - 1 - i, int(trajet.size()) - i, matriceAdj[trajet[i]][trajet[i - 1]]);
        }
    }

    return nouveau;

}

int Graphe::longueurChemin(vector<Sommet *> chemin)
{
    int distance = 0;
    for(int i = 0; i < int(chemin.size())-1;i++)
    {
        distance += matriceAdj[chemin[i]->getIndice()][chemin[i+1]->getIndice()];
    }
    return distance;
}

vector<vector<Sommet *>> Graphe::Dijkstra(Sommet *depart)
{
    vector<int> distances;
    vector<bool> explores;
    vector<vector<Sommet *>> chemins;

    for(int i = 0; i<int(listeSommet.size()); i++)
    {
        if(i == depart->getIndice())
            distances.push_back(0);
        else
            distances.push_back(INT_MAX);
        
        explores.push_back(false);
        chemins.push_back(vector<Sommet *> {depart});
    }

    int distanceMin;
    int aExplorer;
    for(int count = 0; count < int(listeSommet.size()) - 1; count++)
    {
        distanceMin = INT_MAX;
        for(int i = 0; i< int(listeSommet.size());i++)
        {
            if(distances[i] <= distanceMin && !explores[i])
            {
                distanceMin = distances[i];
                aExplorer = i;
            }
        }

        explores[aExplorer] = true;
        for(int i = 0; i < int(listeSommet.size()); i++)
        {
            if(!explores[i] && matriceAdj[aExplorer][i] && distances[aExplorer] != INT_MAX && distances[aExplorer] + matriceAdj[aExplorer][i] < distances[i])
            {
                distances[i] = distances[aExplorer] + matriceAdj[aExplorer][i];
                chemins[i] = chemins[aExplorer];
                chemins[i].push_back(listeSommet[i]);
            }
        }
        
    }
    return chemins;
}

void Graphe::plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture)
{
    vector<vector<vector<Sommet *>>> chemins;
    vector<vector<Sommet *>> intermediaire;
    for(int j = 0; j < int(listeSommet.size()); j++)
        {
            intermediaire.push_back(vector<Sommet *> {listeSommet[j]});
        }
    for(int i = 0; i < int(listeSommet.size());i++)
    { 
        chemins.push_back(intermediaire);
    }
    
    //afin de garder le même système d'indices pour les deux matrices le nouveau graphe aura les mêmes sommets
    //les sommets indésirable seront mis à l'écart grâce à l'absence d'arc avec les autres sommets
    Graphe simplifie = Graphe(this->getSommets());
    int autonomie;
    int longueurArc;
    for(int i = 0; i < int(listeSommet.size());i++)
    {
        //si le sommet est une pompe de carburant, ou le point de départ alors on effectue un dijkstra depuis ce sommet et on ajoute ses arcs sortants
        if(listeSommet[i]->estPompe(voiture->getCarbu()) || i == depart->getIndice())
        {
            chemins[i] = Dijkstra(listeSommet[i]);
            if(i == depart->getIndice() && !depart->estPompe(voiture->getCarbu()))
                autonomie = voiture->getAutonomie();
            else
                autonomie = voiture->getAutonomieMax();
            for(int j = 0; j < int(listeSommet.size()); j++)
            {
                longueurArc = this->longueurChemin(chemins[i][j]);
                if((j == arrivee->getIndice() || listeSommet[j]->estPompe(voiture->getCarbu())) && longueurArc*voiture->getConso() <= autonomie)
                {
                    simplifie.ajouterArc(i, j, longueurArc);
                }
            }
        }
    }

    vector<vector<Sommet *>> cheminsSimplifies = simplifie.Dijkstra(depart);

    vector<vector<Sommet *>> courtChemin;
    Sommet *prochainPoint;
    Sommet *ancienPoint = depart;

    //construction du vrai chemin en concaténant les différents chemins
    for(int i = 0; i < int(cheminsSimplifies[arrivee->getIndice()].size()); i++)
    {
        prochainPoint = cheminsSimplifies[arrivee->getIndice()][i];
        courtChemin.push_back(chemins[ancienPoint->getIndice()][prochainPoint->getIndice()]);
        ancienPoint = prochainPoint;
    }

    if(courtChemin.back().back() != arrivee)
        cout << "Pas d'itinéraire possible" << endl;
    else
    {
        cout << courtChemin[0][0]->getId();
        for (int i = 0; i < int(courtChemin.size()); i++)
        {
            for(int j = 1; j < int(courtChemin[i].size()); j++)
            {
                cout << " -> " << courtChemin[i][j]->getId();
            }
        }
        cout << endl;
        int autonomie;
        cout << "derniere pompe " << courtChemin.back()[0]->getId() << endl;
        if(courtChemin.back()[0]->estPompe(voiture->getCarbu()))
            autonomie = voiture->getAutonomieMax() - longueurChemin(courtChemin.back()) * voiture->getConso();
        else
            autonomie = voiture->getAutonomie() - longueurChemin(courtChemin.back()) * voiture->getConso();
        if(autonomie < 0)
            autonomie = 0;
        voiture->majAutonomie(autonomie);
        cout << endl << "Il reste " << autonomie << "% de carburant" << endl;
    }
    
}