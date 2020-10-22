#ifndef DEF_VEHICULE
#define DEF_VEHICULE

#include <string>

class Vehicule
{
private:
    std::string type_carburant;
    int autonomie_maximale;
    int autonomie;
public:
    Vehicule(std::string carbu, int autonomie_max, int autonomie_depart);
    ~Vehicule();
    void rouler(int distance_parcourue);
    void faire_plein();
};

