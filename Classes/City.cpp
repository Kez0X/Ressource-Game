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

City::City(Player *owner, CitySize size)
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

void City::describe() const {
    std::cout << "Voici la classe City qui permet de connaître le nom du propriétaire de la ville ainsi que la taille de celle-ci" << std::endl;
}