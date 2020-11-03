#include "Graphe.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <climits>

using namespace std;

//constructeur du graphe
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

//affiche le graphe
//pour chaque noeud affiche le noeud et ses voisins
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

//retourne la liste des pointeurs pointants les sommets du graphe
vector<Sommet *> Graphe::getSommets()
{
    return listeSommet;
}

//retrouve un sommet dans la liste de sommet du graphe à l'aide de son id
//retourne un pointeur vers le sommet en question
Sommet *Graphe::trouverSommet(string id){
    for(int i = 0; i<int(listeSommet.size());i++){
        if(listeSommet[i]->getId() == id){
            return listeSommet[i];
        }
    }
    return nullptr;
}

//permet de générer la matrice d'adjacence du graphe
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

//permet d'ajouter un sommet au ggraphe
void Graphe::ajouterSommet(Sommet* sommet)
{
    //récupération du futur indice du sommet dans le vecteur de sommet
    int i = int(listeSommet.size());
    //initialisation du nouveau sommet
    Sommet* nouveau = new Sommet(sommet->getId(), sommet->getType(), i);

    //ajout du sommet à la liste de sommet
    listeSommet.push_back(nouveau);

    //ajout d'une ligne et d'une colonne à la matrice d'adjacence
    //les nouveaux arcs ne sont pas encore générés, les nouvelles valeurs de la matrice sont donc toutes à 0
    matriceAdj.push_back(vector<int>());
    matriceAdj[i].push_back(0);
    for (int j = 0; j < int(listeSommet.size()-1); j++)
    {
        matriceAdj[j].push_back(0);
        matriceAdj[i].push_back(0);
    }
}

//permet d'ajouter un arc à la matrice d'adjacence, à l'aide de l'indice du sommet de départ,
//l'indice du sommet d'arrivée et le coût de cet arc.
void Graphe::ajouterArc(int i, int j, int distance)
{
    matriceAdj[i][j] = distance;
}

//permet d'ajouter un arc à la matrice d'adjacence, cette fois-ci à l'aide de l'id des sommets
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

//retourne la longuer d'un chemin en sommant les coûts de tout les arcs traversés
int Graphe::longueurChemin(vector<Sommet *> chemin)
{
    int distance = 0;
    for(int i = 0; i < int(chemin.size())-1;i++)
    {
        distance += matriceAdj[chemin[i]->getIndice()][chemin[i+1]->getIndice()];
    }
    return distance;
}

//implémentation de l'algorithme de Dijkstra
//retourne un vecteur de vecteur
//chacun de ces sous-vecteurs contient le chemin le plus court entre le sommet de départ
//et le sommet à l'index i dans la liste de sommet du graphe
vector<vector<Sommet *>> Graphe::Dijkstra(Sommet *depart)
{
    //initialisation des variables
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
    //choix du prochain sommet à explorer
    //on choisit le sommet avec la distance la plus courte parmi ceux qui ne sont pas encore explorés
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
        //le sommet est indiqué comme exploré
        explores[aExplorer] = true;

        //observation des voisins
        //si ceux-ci ne sont pas explorés et que 
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


//trouve le plus court chemin entre un sommet de départ et un sommet d'arrivée, en prenant en compte le carburant du véhicule
void Graphe::plusCourtChemin(Sommet *depart, Sommet *arrivee, Vehicule *voiture)
{
    //intialisation des variables
    //chemins[i][j] contient le chemin le plus court du sommet i au sommet j
    //chemins[i] contient les chemins les plus court depuis le sommet i vers tout les autres sommets
    //chemin contient pour chaque sommet, l'ensembles des chemins les plus court depuis celui-ci vers les autres sommets
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
            //recherche des chemins les plus courts
            chemins[i] = Dijkstra(listeSommet[i]);

            //si le sommet est le point de départ et qu'il n'est pas une pompe, c'est l'autonomie restante du dernier trajet qui est utilisé pour borner la taille
            //des arcs admis
            if(i == depart->getIndice() && !depart->estPompe(voiture->getCarbu()))
                autonomie = voiture->getAutonomie();
            //sinon la voiture aura eu l'occasion de se recharger, c'est donc l'autonomie maximale qui est utilisée
            else
                autonomie = voiture->getAutonomieMax();

            
            for(int j = 0; j < int(listeSommet.size()); j++)
            {
                //calcul de la longeur du chemin
                longueurArc = this->longueurChemin(chemins[i][j]);

                //si le sommet j est intéressant (soit c'est une pompe, soit c'est l'arrivée) 
                //et si le chemin peut être parcouru avec l'autonomie disponible au départ du sommet i
                //l'arc est ajouté au graphe
                if((j == arrivee->getIndice() || listeSommet[j]->estPompe(voiture->getCarbu())) && longueurArc*voiture->getConso() <= autonomie)
                {
                    simplifie.ajouterArc(i, j, longueurArc);
                }
            }
        }
    }

    //recherche du chemin le plus court à travers le graphe simplifié
    vector<vector<Sommet *>> cheminsSimplifies = simplifie.Dijkstra(depart);

    vector<vector<Sommet *>> courtChemin;
    Sommet *prochainPoint;
    Sommet *ancienPoint = depart;

    //on obtient le chemin complet en complétant avec les plus courts chemin entre chaque sommet intéressant
    for(int i = 0; i < int(cheminsSimplifies[arrivee->getIndice()].size()); i++)
    {
        prochainPoint = cheminsSimplifies[arrivee->getIndice()][i];
        courtChemin.push_back(chemins[ancienPoint->getIndice()][prochainPoint->getIndice()]);
        ancienPoint = prochainPoint;
    }

    //si le dernier sommet du chemin ne correspond pas à l'arrivée, c'est que cette dernière est inaccessible
    if(courtChemin.back().back() != arrivee)
        cout << "Pas d'itinéraire possible" << endl;
    //sinon affichage du chemin
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
        //mise à jour de l'autonomie restante
        //elle est calculée à partir du coût entre la dernière pompe parcourue et l'arrivée
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
