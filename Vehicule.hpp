
#include <string>
#ifndef DEF_VEHICULE
#define DEF_VEHICULE



class Vehicule
{
private:
    std::string type_carburant;//on peut faire un enum pour chaque type
    int autonomie_maximale;
    int autonomie;
	int taux;

public:
    Vehicule(std::string carbu, int autonomie_max, int autonomie_depart, int taux);
    ~Vehicule();
    void rouler(int distance_parcourue);
    void faire_plein();
};
#endif

