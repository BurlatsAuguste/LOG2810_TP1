#include <string>
#ifndef DEF_VEHICULE
#define DEF_VEHICULE



class Vehicule
{
private:
    std::string typeCarburant;//on peut faire un enum pour chaque type
    int autonomieMax;
    int autonomieRestante;
    int consommation;

public:
    Vehicule();
    Vehicule(std::string carbu, int autonomie, int coeff);
    void rouler(int distanceParcourue);
    void faire_plein();
    int getAutonomie();
    int getAutonomieMax();
    int getConso();
    bool plein(std::string type);
};
#endif