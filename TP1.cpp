#include "Graphe.hpp"
#include "Sommet.hpp"
#include "Vehicule.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

//génère les sommets à l'aide de la string passée en argument
//retourne une liste contenant les pointeurs vers ces sommets
vector<Sommet *> genererSommets(string listeSommet){

    vector<Sommet *> vectorSommet;
    string delimiter = ";";
    size_t pos;
    string token;
    int i = 0;
    
    ////la string est lue morceau par morceau, elle est découpée au niveau des ";"
    while((pos = listeSommet.find(delimiter)) != string::npos){
        token = listeSommet.substr(0, pos);
        listeSommet.erase(0, pos + delimiter.length());

        //création du nouveau sommet à partir des informations données
        Sommet *s = new Sommet(token.substr(0, token.find(',')), token.substr(token.find(',')+1,string::npos), i++);
        vectorSommet.push_back(s);
    }
    return vectorSommet;
}

//retourne un pointeur vers un graphe généré à l'aide des informations contenues dans la strinf passée en argument
Graphe *creerGraphe(string filename)
{
    ifstream file(filename);
    string listeSommet;
    string listeArc;

    //si le nom de fichier donné par l'utilisateur n'est pas bon, la fonction s'arrête et retourne NULL
    if(!file)
    {
        cout << "Impossible d'ouvrir le fichier en lecture" << endl;
        return NULL;
    }

    //les sommets sont générés à l'aide de la première ligne du fichier
    getline(file, listeSommet);
    vector<Sommet *> vectorSommet = genererSommets(listeSommet);

    //les arcs sont générés à l'aide de la seconde ligne du fichier
    getline(file, listeArc);

    //création du graphe
    Graphe *carte = new Graphe(vectorSommet);
    carte->genererMatrice(listeArc);

    return carte;
}

//retourne un pointeur vers un véhicule qui sera généré à l'aide d'informations rentrées par l'utilisateur
Vehicule *initialiserVehicule()
{
    string typeCarburant;
    //l'utilisateur doit rentrer un type de carburant, si celui-ci ne correspond pas aux types disponibles l'utilisateur est à nouveau invité à saisir le type
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

    //l'utilisateur est invité à saisir l'autonomie du véhicule
    //si la saisie n'est pas valide l'utilisateur est invité à recommencer la saisie
    int autonomie;
    cout << "Veuillez indiquer l'autonomie maximale du véhicule" << endl;
    while(true)
    {
        if(cin >> autonomie)
        {
            if(autonomie <= 0)
                cout << "l'autonomie doit être supérieure à 0" << endl;
            else
                break; 
        }
        else
        {
            cout << "Veuillez entrer un nombre entier" << endl;
            cin.clear();
            cin.ignore(1);
        }
    }  

    //l'utilisateur est invité à saisir la consommation du véhicule
    //si la saisie n'est pas valide l'utilisateur est invité à recommencer la saisie
    int consommation;
    cout << "Veuillez indiquer la consommation au kilomètre du véhicule" << endl;
    while (true)
    {
        if(cin >> consommation)
            if(consommation <= 0)
                cout << "la consommation doit être supérieure à 0" << endl;
            else
                break;
        else
        {
            cout << "Veuillez entrer un nombre entier" << endl;
            cin.clear();
            cin.ignore(1);
        }

    }
    
    //initialisation du véhicule
    Vehicule *voiture = new Vehicule(typeCarburant, autonomie, consommation);
    return voiture;
}

void afficherCheminPlusLong(Graphe *carte, Vehicule voiture)
{
    string depart;
    Sommet *sommetDepart;
    //l'utilisateur doit rentrer l'id du sommet de départ, si l'id ne correspond à aucun sommet, l'utilisateur est à nouveau invité à saisir le sommet de départ
    while(true)
    {
        cout << "Veuillez indiquer un point de départ" << endl;
        cin >> depart;
        sommetDepart = carte->trouverSommet(depart);
        if(!sommetDepart)
            cout << "Sommet non valide" << endl;
        else
            break;
    }
    //extraction du sous-graphe resultant du chemin le plus long parcourable par le véhicule
    Graphe plusLong = carte->extractionGraphe(voiture, sommetDepart);
    //affichage du sous-graphe
    plusLong.lireGraphe();
}

void trouverCheminPlusCourt(Graphe *carte, Vehicule *voiture)
{
    string sommet;
    Sommet *depart;
    Sommet *arrivee;
    //l'utilisateur doit rentrer l'id du sommet de départ, si l'id ne correspond à aucun sommet, l'utilisateur est à nouveau invité à saisir le sommet de départ
    while(true)
    {
        cout << "Veuillez indiquer le point de départ" << endl;
        cin >> sommet;
        depart = carte->trouverSommet(sommet);
        if(!depart)
            cout << "Sommet non valide" << endl;
        else
            break;
    }
    //même chose pour le sommet d'arrivée
    while (true)
    {
        cout << "Veuillez indiquer le point d'arrivée" << endl;
        cin >> sommet;
        arrivee = carte->trouverSommet(sommet);
        if(!arrivee)
            cout << "Sommet non valide" << endl;
        else 
            break;
    }
    //recherche du plus court Chemin
    carte->plusCourtChemin(depart, arrivee, voiture);
}


int main(int argc, char *argv[]){

    //initialisation des variables
    int choix_action;
    Graphe *carte = NULL;
    Vehicule *voiture = NULL;
    string filename;

    while(true)
    {
        //affichage du menu
        cout << endl << "Que souhaitez-vous faire ?" << endl
               << "1 Demander les caracteristiques du vehicule"<< endl
               <<"2 Mettre a jour la carte"<< endl
                <<"3 Extraire un sous-graphe"<< endl
               << "4 Determiner le plus court chemin"<< endl
               << "5 Afficher carte" << endl 
                <<"6 Quitter" <<endl;
        //choix de l'action
        if(cin >> choix_action)
        {
            switch(choix_action)
            {
                case 1:
                    voiture = initialiserVehicule();
                    break;
                case 2:
                    cout << "Veuillez entrer le chemin vers le fichier" << endl;
                    cin >> filename;
                    carte = creerGraphe(filename);
                    break;
                case 3:
                    if(!carte || !voiture)
                        cout << "Veuiller rentrer une voiture et un graphe au préalable" <<endl;
                    else
                        afficherCheminPlusLong(carte, *voiture);
                    
                    break;
                case 4:
                    if(!carte || !voiture)
                        cout << "Veuiller rentrer une voiture et un graphe au préalable" <<endl;
                    else
                        trouverCheminPlusCourt(carte, voiture);
                    break;
                case 5:
                    if(!carte)
                        cout << "Veuiller d'abord charger un graphe" << endl;
                    else 
                        carte->lireGraphe();
                    break;
                case 6:
                    cout << "au revoir" << endl;
                    //suppression des pointeurs pour éviter les fuites de mémoire
                    if(carte)
                    {
                        carte->deleteSommet();
                        delete(carte);
                    }
                    if(voiture)
                        delete(voiture);
                    exit(0);
                    break;
                default:
                    cout <<"Veuillez indiquer votre selection par un nombre en 1 et 6" << endl;
            } 
        }
        else
        {
            cout <<"Veuillez indiquer votre selection par un nombre en 1 et 6" << endl;
            cin.clear();
            cin.ignore(1);
        }
        
    }

}
