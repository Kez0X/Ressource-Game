#ifndef CELL_H
#define CELL_H

#include <iostream>
#include "City.hpp"

enum Ressource
{
    Acier,
    Bois,
    Sable,
    Pierre,
    Or,
    Ble,
    Argent,
    Nourriture,
    undefined
};

enum State
{
    normal,
    blocked,
    destroy
};

class Cell
{
private:
    std::string _id;
    Ressource _ressource;
    int _diceNumber;
    City *_city;
    State _state;
    int _remainingEffect;
    Cell *_topcell;
    Cell *_leftcell;
    Cell *_rightcell;
    Cell *_bottomcell;

public:
    // Constructeur
    Cell(const std::string, Ressource, int, State);
    Cell(const std::string, Ressource, int, State, Cell, Cell, Cell, Cell);
    Cell(const std::string, Ressource, int, City, State, Cell, Cell, Cell, Cell);

    // Getters
    const std::string getCellID();
    const Ressource getCellRessource();
    const int getCellDiceNumber();
    const City *getCity();
    const State getState();
    const int getEffectRemainingTime();
    Cell *gettopcell();
    Cell *getleftcell();
    Cell *getrightcell();
    Cell *getbottomcell();

    // Setters
    void setStateBlocked();
    void setStateNormal();
    void setStateDestroy();
    void setEffectRemainingTime(int);
    void setTopcell(Cell *topcell);
    void setLeftcell(Cell *leftcell);
    void setRightcell(Cell *rightcell);
    void setBottomcell(Cell *bottomcell);

    void addCity(City *city);
};

#endif