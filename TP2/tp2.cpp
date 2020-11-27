#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "etat.hpp"
#include "Machine.hpp"

using namespace std;

etat *creerLexique(string filename)
{
    ifstream file(filename);

    //si le nom de fichier donné par l'utilisateur n'est pas bon, la fonction s'arrête et retourne NULL
    if(!file)
    {
        cout << "Impossible d'ouvrir le fichier en lecture" << endl;
        return NULL;
    }
    etat *automate = new etat();
    string mot;
    getline(file, mot);
    while(mot != "")
    {
        automate->ajouterMot(mot, -1);
        getline(file, mot);
    } 
    return automate;
}

void afficherLexique(etat *automate, string mot)
{
    vector<string> lexique = automate->getLexique(mot, -1);
    if(lexique.empty())
        cout << "mot introuvable";
    else
    {
        for(int i = 0; i < int(lexique.size()); i++)
        cout << lexique[i] << endl;
    } 
}

int main(int argc, char const *argv[])
{
    int choix_action;
    string filename;
    string recherche;
    etat *automate =nullptr;

    while (true)
    {
        cout << endl << "Que souhaitez-vous faire ?" << endl
               << "1 Initialisation du jeu"<< endl
               <<"2 Partie contre l'ordinateur"<< endl
                <<"3 Deux joueurs"<< endl
               << "4 Rechercher mot"<< endl 
                <<"5 Quitter" <<endl;
    
    //choix de l'action
        if(cin >> choix_action)
        {
            switch(choix_action)
            {
                case 1:
                    if(automate)
                        delete(automate);
                    cout << "Veuillez entrer le chemin vers le fichier" << endl;
                    cin >> filename;
                    automate = creerLexique(filename);
                    break;
                case 2:
                    if(!automate)
                        cout << "Veuiller au préalable initialiser le jeu " <<endl;
                    else
                        cout << automate->choixAleatoire() << endl;
                    break;
                case 3:
                    //à implanter
                    break;
                case 4:
                    if(!automate)
                        cout << "Veuiller au préalable initialiser le jeu " <<endl;
                    else
                    {
                        cout << "Veuillez entrer votre recherche" << endl;
                        cin >> recherche;
                        afficherLexique(automate, recherche);
                    }
                    break;
                case 5:
                    cout << "au revoir" << endl;
                    //suppression des pointeurs pour éviter les fuites de mémoire
                    delete(automate);
                    exit(0);
                    break;
                default:
                    cout <<"Veuillez indiquer votre selection par un nombre en 1 et 5" << endl;
            } 
        }
        else
        {
            cout <<"Veuillez indiquer votre selection par un nombre en 1 et 5" << endl;
            cin.clear();
            cin.ignore(1);
        }
    }
    return 0;
}
