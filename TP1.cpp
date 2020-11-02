#include "Graphe.hpp"
#include "Sommet.hpp"
#include "Vehicule.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
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
    string typeCarburant;
    while(true)
    {
        cout << "Veuillez indiquer le type de carburant : electrique, essence ou hybrid" << endl;
        cin >> typeCarburant;
        if(typeCarburant == "electrique" || typeCarburant == "essence" || typeCarburant == "hybrid")
        {
            break;
        }
        else
        {
            cout << "Carburant saisi non valide" << endl;
        }
    }

    int autonomie;
    cout << "Veuillez indiquer l'autonomie maximale du véhicule" << endl;
    cin >> autonomie;

    int consommation;
    cout << "Veuillez indiquer la consommation au kilomètre du véhicule" << endl;
    cin >> consommation;
    
    Vehicule *voiture = new Vehicule(typeCarburant, autonomie, consommation);
    return voiture;
}

void afficherCheminPlusLong(Graphe *carte, Vehicule voiture)
{
    string depart;
    cout << "Veuillez indiquer un point de départ" << endl;
    cin >> depart;
    Sommet *sommetDepart = carte->trouverSommet(depart);
    Graphe plusLong = carte->extractionGraphe(voiture, sommetDepart);
    plusLong.lireGraphe();
}

void trouverCheminPlusCourt(Graphe *carte, Vehicule *voiture)
{
    string sommet;
    cout << "Veuillez indiquer le point de départ" << endl;
    cin >> sommet;
    Sommet *depart = carte->trouverSommet(sommet);
    cout << "Veuillez indiquer le point d'arrivée" << endl;
    cin >> sommet;
    Sommet *arrivee = carte->trouverSommet(sommet);
    carte->plusCourtChemin(depart, arrivee, voiture);
}


int main(int argc, char *argv[]){
    int choix_action;
    Graphe *carte = NULL;
    Vehicule *voiture = NULL;
    while(true)
    {
        cout << "Que souhaitez-vous faire ?" << endl
               << "1 Demander les caracteristiques du vehicule"<< endl
               <<"2 Mettre a jour la carte"<< endl
                <<"3 Extraire un sous-graphe"<< endl
               << "4 Determiner le plus court chemin"<< endl
               << "5 Afficher carte" << endl 
               << "6 Afficher autonomie restante" <<endl
                <<"7 Quitter" <<endl; //la 5 est pas demandée dans le TP mais c'est pour tester lireGraphe
        cin >> choix_action;
        string filename;
        switch(choix_action)
        {
            case 1:
                cout << "choix 1 selectionne" << endl;
                voiture = initialiserVehicule();
                break;
            case 2:
                cout << "Veuillez entrer le chemin vers le fichier" << endl;
                cin >> filename;
                carte = creerGraphe(filename);
                break;
            case 3:
                cout << "choix 3 selectionne" << endl;
                if(!carte || !voiture)
                    cout << "Veuiller rentrer une voiture et un graphe au préalable" <<endl;
                else
                    afficherCheminPlusLong(carte, *voiture);
                
                break;
            case 4:
                cout << "choix 4 selectionne" << endl;
                if(!carte || !voiture)
                    cout << "Veuiller rentrer une voiture et un graphe au préalable" <<endl;
                else
                    trouverCheminPlusCourt(carte, voiture);
                break;
            case 5:
                carte->lireGraphe();
                break;
            case 6:
                cout << "Il reste " <<100 * float(voiture->getAutonomie())/float(voiture->getAutonomieMax()) << "% de carburant" << endl;
                break;
            case 7:
                cout << "au revoir" << endl;
                carte->deleteSommet();
                delete(carte);
                delete(voiture);
                exit(0);
                break;
            default:
                cout <<"Veuillez indiquer votre selection par un nombre en 1 et 5" << endl;
                
        }
    }

}
