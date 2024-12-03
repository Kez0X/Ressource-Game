#include <iostream>
#include "Cell.hpp"
#include <cassert>

// Constructeur sans ville
Cell::Cell(const int& id, Ressource ressource, int& diceNumber, State state, Cell topcell, Cell leftcell, Cell rightcell, Cell bottomcell){
    _id = id;
    _ressource = ressource;
    _diceNumber = diceNumber;
    _city = nullptr;
    _state = state;
    _topcell = &topcell;
    _leftcell = &leftcell;
    _rightcell = &rightcell;
    _bottomcell = &bottomcell;
};

// Constructeur avec ville
Cell::Cell(const int& id, Ressource ressource, int& diceNumber, City city, State state, Cell topcell, Cell leftcell, Cell rightcell, Cell bottomcell){
    _id = id;
    _ressource = ressource;
    _diceNumber = diceNumber;
    _city = &city;
    _state = state;
    _topcell = &topcell;
    _leftcell = &leftcell;
    _rightcell = &rightcell;
    _bottomcell = &bottomcell;
};


// Getters
const int Cell::getCellID() {
    return _id;
}

const Ressource Cell::getCellRessource() {
    return _ressource;
}

const int Cell::getCellDiceNumber() {
    return _diceNumber;
}

const City Cell::getCity() {
    return *_city;
}

const State Cell::getState() {
    return _state;
}

// Setters
void Cell::setStateBlocked() {
    _state = blocked;
}

void Cell::setStateNormal() {
    _state = normal;
}

void Cell::setStateDestroy() {
    _state = destroy;
}
