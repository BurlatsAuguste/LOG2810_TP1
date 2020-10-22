#include "Graphe.h"
#include <string>
#include <iostream>
using namespace std;


int main(int argc, char *argv[]){
    int choix_action;
    while(true)
    {
        cout << "Que souhaitez-vous faire ?" << endl
               << "1 Demander les caracteristiques du vehicule"<<endl
               <<"2 Mettre a jour la carte"<<endl
                <<"3 Extraire un sous-graphe"<<endl
               << "4 Determiner le plus court chemin"<<endl
                <<"5 Quitter" <<endl;
        cin >> choix_action;

        switch(choix_action)
        {
            case 1:
                cout << "choix 1 selectionne" << endl;
                break;
            case 2:
                cout << "choix 2 selectionne" << endl;
                break;
            case 3:
                cout << "choix 3 selectionne" << endl;
                break;
            case 4:
                cout << "choix 4 selectionne" << endl;
                break;
            case 5:
                cout << "au revoir" << endl;
                exit(0);
                break;
            default:
                cout <<"Veuillez indiquer votre selection par un nombre en 1 et 5" << endl;
                
        }
    }

}