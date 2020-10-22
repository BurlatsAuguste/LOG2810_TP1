#include <string>
#include "Sommet.h"

using namespace std;

Sommet::Sommet(std::string id, std::string recharge)
{
    identifiant = id;
    type = recharge;
    degre = 0;
}