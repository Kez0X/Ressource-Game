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
        City(Player*, CitySize);

        // Getters
        Player* getOwner() const;
        CitySize getCitySize() const;

        // Setters
        void setTownToCity();

        //Méthodes virtuelles
        //Non utilisée
        virtual void describe() const;

};

#endif