#include <iostream>
#include "Cell.hpp"
#include <cassert>

// Constructeur sans ville
Cell::Cell(const std::string id, Ressource ressource, int diceNumber, State state)
{
    _id = id;
    _ressource = ressource;
    _diceNumber = diceNumber;
    _city = nullptr;
    _state = state;
    _remainingEffect = 0;
    _topcell = nullptr;
    _leftcell = nullptr;
    _rightcell = nullptr;
    _bottomcell = nullptr;
};

// Constructeur sans ville
Cell::Cell(const std::string id, Ressource ressource, int diceNumber, State state, Cell topcell, Cell leftcell, Cell rightcell, Cell bottomcell)
{
    _id = id;
    _ressource = ressource;
    _diceNumber = diceNumber;
    _city = nullptr;
    _state = state;
    _remainingEffect = 0;
    _topcell = &topcell;
    _leftcell = &leftcell;
    _rightcell = &rightcell;
    _bottomcell = &bottomcell;
};

// Constructeur avec ville
Cell::Cell(const std::string id, Ressource ressource, int diceNumber, City city, State state, Cell topcell, Cell leftcell, Cell rightcell, Cell bottomcell)
{
    _id = id;
    _ressource = ressource;
    _diceNumber = diceNumber;
    _city = &city;
    _state = state;
    _remainingEffect = 0;
    _topcell = &topcell;
    _leftcell = &leftcell;
    _rightcell = &rightcell;
    _bottomcell = &bottomcell;
};

// Getters
std::string Cell::getCellID() const
{
    return _id;
}

Ressource Cell::getCellRessource() const
{
    return _ressource;
}

int Cell::getCellDiceNumber() const
{
    return _diceNumber;
}

City *Cell::getCity() const
{
    return _city;
}

State Cell::getState() const
{
    return _state;
}

int Cell::getEffectRemainingTime() const
{
    return _remainingEffect;
}

Cell *Cell::gettopcell() const
{
    return _topcell;
};

Cell *Cell::getleftcell() const
{
    return _leftcell;
};

Cell *Cell::getrightcell() const
{
    return _rightcell;
};

Cell *Cell::getbottomcell() const
{
    return _bottomcell;
};

// Setters
void Cell::setStateBlocked()
{
    _state = blocked;
}

void Cell::setStateNormal()
{
    _state = normal;
}

void Cell::setStateDestroy()
{
    _state = destroy;
}

void Cell::setEffectRemainingTime(int _turnN)
{
    _remainingEffect = _turnN;
}

void Cell::setTopcell(Cell *topcell)
{
    _topcell = topcell;
};

void Cell::setLeftcell(Cell *leftcell)
{
    _leftcell = leftcell;
};

void Cell::setRightcell(Cell *rightcell)
{
    _rightcell = rightcell;
};

void Cell::setBottomcell(Cell *bottomcell)
{
    _bottomcell = bottomcell;
};

void Cell::addCity(City *city)
{
    _city = city;
};