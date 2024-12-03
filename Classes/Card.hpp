#ifndef CITY_H
#define CITY_H

#include <string>
#include <Cell.hpp>

enum Rarete {
    commun,
    rare,
    epique
};

class Card {
    private:
        std::string _desc;
        Rarete _rarete;
        Ressource _ressource;
        Bonus _bonus;
};

#endif