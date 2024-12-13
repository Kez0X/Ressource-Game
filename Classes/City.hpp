#ifndef CITY_H
#define CITY_H

#include "Player.hpp"

enum CitySize {
    big_city,
    small_town,
};

class City {
    private:
        CitySize _size;
        Player* _owner;

    public:
        // Constructeurs
        City(Player*);
        City(CitySize, Player*);

        // Getters
        Player* getOwner() const;
        CitySize getCitySize() const;

        // Setters
        void setTownToCity();
};

#endif