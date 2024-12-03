#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <City.hpp>

enum Ressource
{
    Acier,
    Bois,
    Sable,
    Pierre,
    Or,
    Ble,
    Argent,
    Nourriture
};

enum State{
    normal,
    blocked,
    destroy
};

class Cell
{
private:
    int _id;
    Ressource _ressource;
    int _diceNumber;
    City _city;
    State _state;
    Cell* topcell;
    Cell* leftcell;
    Cell* rightcell;
    Cell* bottomcell;

public:
    // Constructeur
    Cell(const int&, Ressource, int&);
    Cell(const int&, Ressource, int&, City);

    // Getters
    const int getCellID();
    const Ressource getCellRessource();
    const int getCellDiceNumber();
    const City getCity();
    const State getState();

    //Setters
    void setStateBlocked();
    void setStateNormal();
    void setStateDestroy();
    
};

#endif