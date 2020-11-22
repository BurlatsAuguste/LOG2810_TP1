#include <vector>
#include <string>
#include <map>

#ifndef DEF_NOEUD
#define DEF_NOEUD

class noeud
{
private:
    std::string valeur;
    std::map<char, noeud *> enfants;

public:
    noeud(std::string val);
    ~noeud();
    void ajouterMot(std::string mot, int indice);
    noeud *trouverFils(char lettre);
    std::vector<std::string> getLexique(std::string debut, int indice);
    std::vector<std::string> getToutFils();
};


#endif