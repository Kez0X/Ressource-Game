#ifndef CITY_H
#define CITY_H

class Player;

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
        Player* getOwner();
        CitySize getCitySize();

        // Setters
        void setTownToCity();
};

#endif