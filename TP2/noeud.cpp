#include <vector>
#include <string>
#include <iostream>
#include "noeud.hpp"

using namespace std;

noeud::noeud(string val):valeur{val}{}

noeud::~noeud()
{
    map<char, noeud *>::iterator it;
    for(it = enfants.begin(); it != enfants.end(); it++)
    {
        delete(it->second);
    }
}

void noeud::ajouterMot(string mot, int indice)
{
    if(int(mot.length())-1 == indice)
    {
        valeur = mot;
    }
    else
    {
        indice ++;
        noeud *fils = trouverFils(mot.at(indice));
        if(fils == NULL)
        {
            fils = new noeud("");
            //cout << mot.at(indice) << " ; " << fils << endl;
            enfants.insert(map<char, noeud*>::value_type(mot.at(indice), fils));
        }
        fils->ajouterMot(mot, indice);
    }
}

noeud *noeud::trouverFils(char lettre)
{
    map<char, noeud *>::iterator it;
    it = enfants.find(lettre);
    if(it == enfants.end())
        return NULL;
    return enfants.at(lettre);
}

vector<string> noeud::getToutFils()
{
    vector<string> lexique;
    vector<string> lexiqueFils;
    if(!valeur.empty())
        lexique.push_back(valeur);
    
    for(map<char, noeud *>::iterator it = enfants.begin(); it != enfants.end(); it++)
    {
        lexiqueFils = it->second->getToutFils();
        lexique.insert(lexique.end(), lexiqueFils.begin(), lexiqueFils.end());
    }
    return lexique;   
}

vector<string> noeud::getLexique(string mot, int indice)
{
    vector<string> lexique;
    if(int(mot.length())-1 == indice)
    {
        lexique = getToutFils();
    }
    else
    {
        indice++;
        noeud *fils = trouverFils(mot.at(indice));
        if(fils == NULL)
            lexique = {};
        else
        {
            lexique = fils->getLexique(mot, indice);
        }  
    }
    return lexique;
}

