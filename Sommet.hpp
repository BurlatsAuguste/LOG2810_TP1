#include <string>
#include <vector>

#ifndef DEF_SOMMET
#define DEF_SOMMET




class Sommet
{
private:
    std::string identifiant;
    std::string type;
    std::vector<Sommet *> voisins;
    int degre;

public:
    Sommet(std::string id, std::string recharge);
    void updateDegre(int deg);
    std::string getId();
    std::string getType();
    std::vector<Sommet *> getVoisins();
    int getDegre();
    void updateVoisins(std::vector<Sommet *> voisinage);
    void addVoisin(Sommet * sommet);
};
#endif


