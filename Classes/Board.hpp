#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Cell.hpp"
#include <vector>
#include <string>
#include <map>

class Board
{

protected:
// Les données des cases et des dès
// Les dictionnaires suivants ne sont utilisés uniquement dans le cadre de méthodes présentes dans la classe
    std::map<std::string, std::map<Ressource, int>> _map_cases;
    std::map<std::string, std::vector<int>> _map_dice;

private:
    // Le tableau de cases
    std::map<std::string, Cell*> _board;
    // La fonction de tirage d'une ressource présente dans la classe mais peut être utilisés au sein d'autres classes
    void drawRessource(Ressource*, std::string*);

public:
    // Constructeur
    Board();

    // Méthodes utilisées au sein des autres classes et qui permettent de récupérer des données et d'en afficher
    Cell* getCellByIndex(std::string);
    std::vector<Cell*> getCellsbyDiceNumber(int);
    std::vector<Cell *> getTowns();

    void printBoard();

    std::string ressourceToString(Ressource);

    
};

#endif