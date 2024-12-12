#include <iostream>
#include "City.hpp"
#include "Player.hpp"
#include <cassert>

// Constructeurs
City::City(Player *owner)
{
    _size = small_town;
    _owner = owner;
};

City::City(CitySize size, Player *owner)
{
    _size = size;
    _owner = owner;
};

// Getters
CitySize City::getCitySize() const
{
    return _size;
};

Player *City::getOwner() const
{
    return _owner;
};

// Setters
void City::setTownToCity()
{
    _size = big_city;
};