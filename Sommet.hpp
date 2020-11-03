#include <string>
#include <vector>

#ifndef DEF_SOMMET
#define DEF_SOMMET




class Sommet
{
private:
    std::string identifiant;
    std::string type;
    int indice;

public:
    Sommet(std::string id, std::string recharge, int indi);
    std::string getId();
    std::string getType();
    int getIndice();
};
#endif


