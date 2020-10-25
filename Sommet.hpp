#include <string>

#ifndef DEF_SOMMET
#define DEF_SOMMET




class Sommet
{
private:
    std::string identifiant;
    std::string type;
    int degre;

public:
    Sommet(std::string id, std::string recharge);
    void updateDegre(int deg);
    std::string getId();
    std::string getType();
    int getDegre();
};
#endif


