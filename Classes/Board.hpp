#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <Cell.hpp>
#include <vector>
#include <string>

class Board
{
private:
    std::vector<Cell*> _board;
    std::map<std::string, std::map<Ressource, int>> map_cases

public:
    // Constructeur
    Board();
    
};

#endif