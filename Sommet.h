#ifndef DEF_SOMMET
#define DEF_SOMMET
#endif

#include <string>

class Sommet
{
private:
    std::string identifiant;
    std::string type;
    int degre;

public:
    Sommet(std::string id, std::string recharge);
    ~Sommet();
    void update_degre(int deg);
    std::string getId();
    std::string getType();
    int getDegre();
};



