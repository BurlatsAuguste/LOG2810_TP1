#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <random>
#include "etat.hpp"

using namespace std;

etat::~etat()
{
    map<char, etat *>::iterator it;
    for(it = enfants.begin(); it != enfants.end(); it++)
    {
        delete(it->second);
    }
}

void etat::ajouterMot(string mot, int indice)
{
    if(int(mot.length())-1 == indice)
    {
        terminal = true;
    }
    else
    {
        indice ++;
        etat *fils = trouverFils(mot.at(indice));
        if(fils == nullptr)
        {
            fils = new etat();
            enfants.insert(map<char, etat*>::value_type(mot.at(indice), fils));
        }
        fils->ajouterMot(mot, indice);
    }
}

etat *etat::trouverFils(char lettre)
{
    map<char, etat *>::iterator it;
    it = enfants.find(lettre);
    if(it == enfants.end())
        return nullptr;
    return enfants.at(lettre);
}

vector<string> etat::getToutFils(string debut)
{
    vector<string> lexique;
    queue<pair<string, etat*>> aExplorer;
    map<char, etat *>::iterator it;
    etat *etatCourant;
    string chaineCourante;

    if(terminal)
    {
        lexique.push_back(debut);
    }

    for(it = enfants.begin(); it != enfants.end(); it++)
    {
        aExplorer.push({debut+it->first, it->second});
    }

    cout << aExplorer.size() << endl;
    cout << enfants.size() << endl;
    while (!aExplorer.empty())
    {
        etatCourant = aExplorer.front().second;
        chaineCourante = aExplorer.front().first;   
        if(etatCourant->terminal)
            lexique.push_back(chaineCourante);
        
        for(it = etatCourant->enfants.begin(); it != etatCourant->enfants.end(); it++)
        {
            aExplorer.push({chaineCourante+it->first, it->second});
        }
        aExplorer.pop();
    }
    
    return lexique;
}

vector<string> etat::getLexique(string mot, int indice)
{
    vector<string> lexique;
    if(int(mot.length())-1 == indice)
    {
        lexique = getToutFils(mot);
    }
    else
    {
        indice++;
        etat *fils = trouverFils(mot.at(indice));
        if(fils == nullptr)
            lexique = {};
        else
        {
            lexique = fils->getLexique(mot, indice);
        }  
    }
    return lexique;
}

string etat::choixAleatoire()
{
    vector<string> lexique = getLexique("", -1);
    random_device generator;
    uniform_int_distribution<int> tirage(0, lexique.size()-1);
    return lexique[tirage(generator)];
}

