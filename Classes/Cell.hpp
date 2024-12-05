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
    City* _city;
    State _state;
    Cell* _topcell;
    Cell* _leftcell;
    Cell* _rightcell;
    Cell* _bottomcell;

public:
    // Constructeur
    Cell(const int&, Ressource, int&, State,  Cell, Cell, Cell, Cell);
    Cell(const int&, Ressource, int&, City, State, Cell, Cell, Cell, Cell);

    // Getters
    const int getCellID();
    const Ressource getCellRessource();
    const int getCellDiceNumber();
    const City getCity();
    const State getState();
    Cell* gettopcell();
    Cell* getleftcell();
    Cell* getrightcell();
    Cell* getbottomcell();


    //Setters
    void setStateBlocked();
    void setStateNormal();
    void setStateDestroy();
    
};

#endif