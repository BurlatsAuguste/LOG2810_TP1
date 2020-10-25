#include "Graphe.hpp"
#include "Arc.hpp"
#include "Sommet.hpp"
#include "Vehicule.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//fonction pour générer les sommets
vector<Sommet> genererSommets(string listeSommet){
    vector<Sommet> vectorSommet;
    string delimiter = ";";
    size_t pos;
    string token;
    //on découpe la string au niveau des ; et on génère un sommet avec chaque morceau
    while((pos = listeSommet.find(delimiter)) != string::npos){
        token = listeSommet.substr(0, pos);
        listeSommet.erase(0, pos + delimiter.length());
        Sommet *s = new Sommet(token.substr(0, token.find(',')), token.substr(token.find(',')+1,string::npos));
        vectorSommet.push_back(*s);
    }
    return vectorSommet;
}

//fonction servant à retrouver un sommet dans un vecteur à l'aide de son id
Sommet *trouverSommet(string id, vector<Sommet> vectorSommet){
    for(int i = 0; i<int(vectorSommet.size());i++){
        if(vectorSommet[i].getId() == id){
            return &vectorSommet[i];
        }
    }
}

//fonction pour générer les arcs
vector<Arc> genererArcs(string listeArc, vector<Sommet> vectorSommet){
    vector<Arc> vectorArc;
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

        depart = trouverSommet(token.substr(0, token.find(',')), vectorSommet);
        token.erase(0, token.find(',')+1);

        arrivee = trouverSommet(token.substr(0, token.find(',')), vectorSommet);
        token.erase(0, token.find(',')+1);

        distance = stoi(token);

        Arc *a = new Arc(depart, arrivee, distance);
        vectorArc.push_back(*a);
    }
    return vectorArc;
}

//fonction pour générer un graphe
Graphe *creerGraphe(string filename)
{
    ifstream file(filename);
    string listeSommet;
    string listeArc;

    //on génère les sommets à l'aide de la première ligne du fichier
    getline(file, listeSommet);
    vector<Sommet> vectorSommet = genererSommets(listeSommet);

    //on génère les arcs à l'aide de la seconde ligne du fichier
    getline(file, listeArc);
    vector<Arc> vectorArc = genererArcs(listeArc, vectorSommet);

    Graphe *carte = new Graphe(vectorSommet, vectorArc);
    carte->updateDegre();
    carte->updateVoisins();

    return carte;
}


int main(int argc, char *argv[]){
    int choix_action;
    Graphe *carte;
    while(true)
    {
        cout << "Que souhaitez-vous faire ?" << endl
               << "1 Demander les caracteristiques du vehicule"<<endl
               <<"2 Mettre a jour la carte"<<endl
                <<"3 Extraire un sous-graphe"<<endl
               << "4 Determiner le plus court chemin"<<endl
               << "5 Afficher carte" << endl 
                <<"6 Quitter" <<endl; //la 5 est pas demandée dans le TP mais c'est pour tester lireGraphe
        cin >> choix_action;
        string filename;
        switch(choix_action)
        {
            case 1:
                cout << "choix 1 selectionne" << endl;
                break;
            case 2:
                cout << "Veuillez entrer le chemin vers le fichier" << endl;
                cin >> filename;
                carte = creerGraphe(filename);
                break;
            case 3:
                cout << "choix 3 selectionne" << endl;
                break;
            case 4:
                cout << "choix 4 selectionne" << endl;
                break;
            case 5:
                carte->lireGraphe();
            case 6:
                cout << "au revoir" << endl;
                delete(carte);
                exit(0);
                break;
            default:
                cout <<"Veuillez indiquer votre selection par un nombre en 1 et 5" << endl;
                
        }
    }

}