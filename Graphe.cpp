#include "Graphe.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <climits>

using namespace std;

//constructeur du graphe
//la liste de sommet donnée en argument est utilisée comme liste des sommets du graphe
//la matrice d'adjacence est initialisée avec toute les valeurs à 0
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

//permet de supprimer tout les pointeurs des sommets afin d'éviter les fuites de mémoire
void Graphe::deleteSommet()
{
    for(int i = 0; i < int(listeSommet.size()); i++)
    {
        delete(listeSommet[i]);
    }
}

Graphe& Graphe::operator=(const Graphe& other) {

    for (int i = 0; i < int(listeSommet.size()); i++)
    {
        delete(listeSommet[i]);
    }
    listeSommet.clear();

    int size = other.listeSommet.size();
    for (int i = 0; i < size; i++)
    {
        listeSommet.push_back(new Sommet(other.listeSommet[i]->getId(), other.listeSommet[i]->getType(), i));
        matriceAdj.push_back(vector<int>());
        for (int j = 0; j < size; j++)
        {
            matriceAdj[i].push_back(other.matriceAdj[i][j]);
        }
    }
    return *this;

}

//affiche le graphe
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

//retourne la liste de sommet du graphe
vector<Sommet *> Graphe::getSommets()
{
    return listeSommet;
}

//renvoit le pointeur vers le sommet dont l'id est passé en argument
Sommet *Graphe::trouverSommet(string id){
    for(int i = 0; i<int(listeSommet.size());i++){
        if(listeSommet[i]->getId() == id){
            return listeSommet[i];
        }
    }
    return nullptr;
}

//permet de mettre à jour la matrice d'adjacence en ajoutant les coûts des arcs aux valeurs correspondantes
void Graphe::genererMatrice(string listeArc){
    string delimiter = ";";
    size_t pos;
    string token;
    Sommet *depart;
    Sommet * arrivee;
    int distance;
    //la string est lue morceau par morceau, elle est découpée au niveau des ";"
    while((pos = listeArc.find(delimiter)) != string::npos){
        token = listeArc.substr(0, pos);
        listeArc.erase(0, pos + delimiter.length());

        //identification du sommet de départ
        depart = trouverSommet(token.substr(0, token.find(',')));
        token.erase(0, token.find(',') + 1);

        //identification du sommet d'arrivée
        arrivee = trouverSommet(token.substr(0, token.find(',')));
        token.erase(0, token.find(',') + 1);

        //récupération du cout de l'arc
        distance = stoi(token);

        //mise à jour de la matrice d'adjacence
        matriceAdj[depart->getIndice()][arrivee->getIndice()] = distance;
    }

}

//ajoute le sommet passé en argument à la liste de sommet du graphe
//et ajoute une ligne et une colonne remplies de 0 à la matrice d'adjacence
void Graphe::ajouterSommet(Sommet* sommet)
{

    string id = sommet->getId();
    string type = sommet->getType();
    int i = int(listeSommet.size());

    listeSommet.push_back(new Sommet(id, type, i));
    matriceAdj.push_back(vector<int>());
    matriceAdj[i].push_back(0);
    for (int j = 0; j < int(listeSommet.size()) - 1; j++)
    {
        matriceAdj[j].push_back(0);
        matriceAdj[i].push_back(0);
    }
}

//crée un sommet avec les informations passées en arguments et l'ajoute à la liste de sommet
//et ajoute une ligne et une colonne remplies de 0 à la matrice d'adjacence
void Graphe::ajouterSommet(string id, string type)
{
    int i = int(listeSommet.size());
    listeSommet.push_back(new Sommet(id, type, i));
    matriceAdj.push_back(vector<int>());
    matriceAdj[i].push_back(0);
    for (int j = 0; j < int(listeSommet.size()) - 1; j++)
    {
        matriceAdj[j].push_back(0);
        matriceAdj[i].push_back(0);
    }
}

//remplace la valeur de la matrice d'adjacence aux indices passés en arguments par la distance passée en argument
void Graphe::ajouterArc(int i, int j, int distance)
{
    matriceAdj[i][j] = distance;
}

//remplace la valeur de la matrice d'adjacence aux indices passés en arguments par la distance passée en argument
void Graphe::ajouterArc(string id1, string id2, int distance)
{
    int i = trouverSommet(id1)->getIndice();
    int j = trouverSommet(id2)->getIndice();
    ajouterArc(i, j, distance);
}

vector<int> Graphe::plusLong(set<Sommet*> visites, Sommet* depart, int restant, int consommation)
{
    int i = depart->getIndice();

    int max = 0;
    vector<int> trajet;
    bool end = true;


    for (int arc = 0; arc < int(listeSommet.size()); arc++)
    {
        if (matriceAdj[i][arc] != 0 && matriceAdj[i][arc] * consommation <= restant && visites.count(listeSommet[arc]) == 0)
        {
            set<Sommet*> copie = visites;
            copie.insert(listeSommet[arc]);
            vector<int> chemin = plusLong(copie, listeSommet[arc], restant - matriceAdj[i][arc] * consommation, consommation);
            int distance = chemin[0] + matriceAdj[i][arc];
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

Graphe Graphe::extraction(int autonomie, int conso, int d)
{
    Graphe rep = Graphe();
    Sommet* depart = listeSommet[d];
    rep.ajouterSommet(depart->getId(), depart->getType());
    for (int i = 0; i < int(matriceAdj[d].size()); i++)
    {
        if (matriceAdj[d][i] != 0 && matriceAdj[d][i]*conso<=autonomie)
        {
            Graphe nouveau = extraction(autonomie - matriceAdj[d][i]*conso, conso, i);
            rep += nouveau;
            rep.ajouterArc(depart->getId(), listeSommet[i]->getId(), matriceAdj[d][i]);
        }
    }

    return rep;


}

Graphe& Graphe::operator+=(Graphe& other)
{
    for (int j=0; j<int(other.listeSommet.size()) ; j++)
    {
        if (trouverSommet(other.listeSommet[j]->getId()) == nullptr)
            ajouterSommet(other.listeSommet[j]->getId(), other.listeSommet[j]->getType());
    }
    for (int i = 0; i < int(other.matriceAdj.size()); i++)
    {
        for (int j = 0; j < int(other.matriceAdj[i].size()); j++)
        {
            if (other.matriceAdj[i][j] != 0)
                ajouterArc(other.listeSommet[i]->getId(), other.listeSommet[j]->getId(), other.matriceAdj[i][j]);
        }
    }
    return *this;
}


vector<pair<int, string>> Graphe::Dijkstra(Sommet* depart)
{
    set<Sommet*> visites;
    vector<pair<int, string>> rep;

    for (Sommet* s : listeSommet)
    {
        if (s == depart)
            rep.push_back(make_pair(0, ""));

        else
            rep.push_back(make_pair(INT_MAX, ""));
    }

    while (visites.size() < listeSommet.size())
    {
        Sommet* nouveau = nullptr;
        int dmin = INT_MAX;
        int indice = -1;
        for (int i = 0; i < int(rep.size()); i++)
        {
            if (rep[i].first < dmin && visites.count(listeSommet[i])==0)
            {
                dmin = rep[i].first;
                nouveau = listeSommet[i];
                indice = i;
            }
        }
        if (indice == -1)
            break;

        visites.insert(nouveau);

        for (int j = 0; j < int(matriceAdj[indice].size()); j++)
        {
            if (matriceAdj[indice][j] != 0 && visites.count(listeSommet[j]) == 0)
            {
                if (rep[j].first > rep[indice].first + matriceAdj[indice][j])
                {
                    rep[j].first = rep[indice].first + matriceAdj[indice][j];
                    rep[j].second = rep[indice].second + listeSommet[j]->getId();
                }
            }
        }
    }

    return rep;
}

//retourne un nouveau graphe résultant du plus long chemin que peut parcourir le véhicule
//passé en argument depuis le sommet passé en argument
Graphe Graphe::extractionGraphe(Vehicule v, Sommet* depart)
{
    //ce set sert à mémoriser les sommets déjà visités
    set<Sommet*> visites;
    visites.insert(depart);

    //recherche du chemin le plus long
    vector<int> trajet = plusLong(visites, depart, v.getAutonomieMax(), v.getConso());

    //génération du nouveau graphe
    Graphe nouveau;
    for (int i=int(trajet.size())-1; i > 0 ; i--)
    {
        nouveau.ajouterSommet(listeSommet[trajet[i]]);
    }
    for (int j = int(trajet.size()) - 1; j > 0; j--)
    {
        if (j > 1)
        {
            nouveau.ajouterArc(int(trajet.size()) - 1 - j, int(trajet.size()) - j, matriceAdj[trajet[j]][trajet[j - 1]]);
        }
    }
    
    cout << "Chemin le plus long de longeur " << trajet[0] << endl;
    return nouveau;

}


void Graphe::plusCourtChemin(Sommet* depart, Sommet* arrivee, Vehicule *voiture)
{
    map<string, string> banque;

    Graphe nouveau;
    nouveau.ajouterSommet(depart);

    Graphe debut = extraction(voiture->getAutonomie(), voiture->getConso(), depart->getIndice());
    vector<pair<int, string>> chemins = debut.Dijkstra(debut.getSommets()[0]);
    for(Sommet* s : debut.getSommets())
    {
        if(voiture->plein(s->getType()) || s->getId().compare(arrivee->getId())==0)
        {
            nouveau.ajouterSommet(s);
            nouveau.ajouterArc(debut.getSommets()[0]->getId(), s->getId(), chemins[s->getIndice()].first);
            banque[debut.getSommets()[0]->getId()+s->getId()] = chemins[s->getIndice()].second;
        }

    }

    for (int i=0; i<int(listeSommet.size()); i++)
    {
        if (voiture->plein(listeSommet[i]->getType()))
        {
            nouveau.ajouterSommet(listeSommet[i]);

            Graphe sous = extraction(voiture->getAutonomieMax(), voiture->getConso(), i);
            chemins = sous.Dijkstra(sous.getSommets()[0]);
            for(Sommet* s2 : sous.getSommets())
            {
                if(voiture->plein(s2->getType())|| s2->getId().compare(arrivee->getId())==0)
                {
                    nouveau.ajouterSommet(s2);
                    nouveau.ajouterArc(listeSommet[i]->getId(), s2->getId(), chemins[s2->getIndice()].first);
                    banque[sous.getSommets()[0]->getId()+s2->getId()] = chemins[s2->getIndice()].second;
                }

            }
        }
    }

    Sommet * fin = nouveau.trouverSommet(arrivee->getId());


    vector<pair<int, string>> final = nouveau.Dijkstra(nouveau.trouverSommet(depart->getId()));
    if (fin==nullptr || final[fin->getIndice()].first ==  INT_MAX)
    {
        cout<<"Erreur";
        return;
    }



    string trajet = final[fin->getIndice()].second;
    trajet = depart->getId()+trajet;
    string rep;
    for (int i=0; i<int(trajet.size())-1; i++)
    {
        rep += banque[trajet.substr(i,2)];

    }

    cout << depart->getId();
    for (int i = 0; i < int(rep.size()); i++)
    {
        cout << "->" << rep.substr(i, 1);
    }
    cout << endl;
    cout<<"Distance : " << final[fin->getIndice()].first<<endl;
    voiture->rouler(final[fin->getIndice()].first);
    cout << "Il reste " << 100*float(voiture->getAutonomie())/float(voiture->getAutonomieMax()) << "% de carburant" << endl;
}














