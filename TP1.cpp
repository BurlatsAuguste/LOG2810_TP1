#include "Graphe.hpp"
#include "Sommet.hpp"
#include "Vehicule.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//fonction pour générer les sommets
vector<Sommet *> genererSommets(string listeSommet){
    vector<Sommet *> vectorSommet;
    string delimiter = ";";
    size_t pos;
    string token;
    int i = 0;
    //on découpe la string au niveau des ; et on génère un sommet avec chaque morceau
    while((pos = listeSommet.find(delimiter)) != string::npos){
        token = listeSommet.substr(0, pos);
        listeSommet.erase(0, pos + delimiter.length());
        Sommet *s = new Sommet(token.substr(0, token.find(',')), token.substr(token.find(',')+1,string::npos), i++);
        vectorSommet.push_back(s);
    }
    return vectorSommet;
}

//fonction pour générer un graphe
Graphe *creerGraphe(string filename)
{
    ifstream file(filename);
    string listeSommet;
    string listeArc;

    //on génère les sommets à l'aide de la première ligne du fichier
    getline(file, listeSommet);
    vector<Sommet *> vectorSommet = genererSommets(listeSommet);

    //on génère les arcs à l'aide de la seconde ligne du fichier
    getline(file, listeArc);
    //vector<Arc *> vectorArc = genererArcs(listeArc, vectorSommet);

    Graphe *carte = new Graphe(vectorSommet);
    carte->genererMatrice(listeArc);

    return carte;
}

Vehicule *initialiserVehicule()
{

}


int main(int argc, char *argv[]){
    int choix_action;
    Graphe *carte;
    bool executeA = false;
    while(true)
    {
        cout << "Que souhaitez-vous faire ?" << endl
               << "1 Demander les caracteristiques du vehicule"<< endl
               <<"2 Mettre a jour la carte"<< endl
                <<"3 Extraire un sous-graphe"<< endl
               << "4 Determiner le plus court chemin"<< endl
               << "5 Afficher carte" << endl 
                <<"6 Quitter" <<endl; //la 5 est pas demandée dans le TP mais c'est pour tester lireGraphe
        cin >> choix_action;
        string filename;
        switch(choix_action)
        {
            case 1:
                cout << "choix 1 selectionne" << endl;
                executeA = true;
                break;
            case 2:
                cout << "Veuillez entrer le chemin vers le fichier" << endl;
                cin >> filename;
                carte = creerGraphe(filename);
                break;
            case 3:
                cout << "choix 3 selectionne" << endl;
                if(!executeA)
                {
                    //message d'erreur
                }
                break;
            case 4:
                cout << "choix 4 selectionne" << endl;
                break;
            case 5:
                carte->lireGraphe();
                break;
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
