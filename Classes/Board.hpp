#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Cell.hpp"
#include <vector>
#include <string>
#include <map>

class Board
{
private:
    // Le tableau de cases
    std::map<std::string, Cell*> _board;

    // Les données des cases
    std::map<std::string, std::map<Ressource, int>> _map_cases;
    std::map<std::string, std::vector<int>> _map_dice;

    // La fonction de tirage d'une ressource
    void drawRessource(Ressource*, std::string*);

public:
    // Constructeur
    Board();
    
};

#endif