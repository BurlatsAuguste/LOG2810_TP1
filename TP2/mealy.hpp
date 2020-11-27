#include <string>

#ifndef DEF_MEALY
#define DEF_MEALY

class mealy
{
private:
    int id;
    char lettre;
    mealy *suivant;
public:
    mealy(int identifiant, char l);
    ~mealy();
    int compteErreur(std::string mot, int indice);
    void ajoutSuivant(mealy *etat);
};


#endif