
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
    void majAutonomie(int newAutonomie);
    int getAutonomie();
    int getAutonomieMax();
    int getConso();
    std::string getCarbu();
};
#endif

