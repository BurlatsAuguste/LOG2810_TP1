
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
    void majAutonomie(int newAutonomie);
    void fairePlein(std::string carburant);
    int getAutonomie();
    int getAutonomieMax();
    int getConso();
};
#endif

