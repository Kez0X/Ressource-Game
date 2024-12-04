#include <iostream>
#include "City.hpp"
#include <cassert>

// Constructeurs
City::City(Player owner){
    _size = small_town;
    _owner = owner;
};

City::City(CitySize size, Player owner){
    _size = size;
    _owner = owner;
};

// Getters
const CitySize City::getCitySize(){
    return _size;
};

const Player City::getOwner(){
    return _owner;
};

// Setters
void City::setTownToCity(){
    _size = big_city;
};