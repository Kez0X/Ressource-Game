#include "Board.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <random>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

int randomInt2()
{
    std::srand(std::time(NULL));
    return std::rand();
}

Board::Board()
{
    _map_cases = {{"commun", {{Acier, 6}, {Bois, 10}, {Sable, 9}, {Ble, 9}, {Nourriture, 8}}}, {"rare", {{Pierre, 4}}}, {"épique", {{Argent, 2}, {Or, 1}}}};
    _map_dice = {{"commun", {5, 6, 7, 8, 9}}, {"rare", {3, 4, 10, 11}}, {"épique", {1, 2, 12}}};

    // Initialisation de la graine
    srand(std::time(NULL));

    // Création des cellules indépendantes
    for (char row = 'a'; row < 'h'; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);

            // Tirage de la ressource aléatoire
            Ressource *cellRessource = new Ressource;
            std::string *cellRarity = new std::string;
            drawRessource(cellRessource, cellRarity);

            // Choix du numéro du dés
            int cellDiceNumber = _map_dice[*cellRarity][rand() % _map_dice[*cellRarity].size()];

            // Génération de la cellule
            _board[index] = new Cell(index, *cellRessource, cellDiceNumber, normal);

            delete cellRessource;
            delete cellRarity;
        }
    }

    // Liaison des cellules entres elles
    for (char row = 'a'; row < 'h'; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);
            if (index == "a0")
            {
                std::string indexRight = row + std::to_string(column + 1);
                Cell *rightCell = _board[indexRight];

                std::string indexBottom = char(row + 1) + std::to_string(column);
                Cell *bottomCell = _board[indexBottom];

                _board[index]->setRightcell(rightCell);
                _board[index]->setBottomcell(bottomCell);
            }

            if (index == "a6")
            {
                std::string indexLeft = row + std::to_string(column - 1);
                Cell *leftCell = _board[indexLeft];

                std::string indexBottom = char(row + 1) + std::to_string(column);
                Cell *bottomCell = _board[indexBottom];

                _board[index]->setLeftcell(leftCell);
                _board[index]->setBottomcell(bottomCell);
            }

            if (index == "g0")
            {
                std::string indexTop = char(row - 1) + std::to_string(column);
                Cell *topCell = _board[indexTop];

                std::string indexRight = row + std::to_string(column + 1);
                Cell *rightCell = _board[indexRight];

                _board[index]->setTopcell(topCell);
                _board[index]->setRightcell(rightCell);
            }

            if (index == "g6")
            {
                std::string indexTop = char(row - 1) + std::to_string(column);
                Cell *topCell = _board[indexTop];

                std::string indexLeft = row + std::to_string(column - 1);
                Cell *leftCell = _board[indexLeft];

                _board[index]->setTopcell(topCell);
                _board[index]->setLeftcell(leftCell);
            }

            if (row == 'a')
            {
                std::string indexLeft = row + std::to_string(column - 1);
                std::string indexRight = row + std::to_string(column + 1);
                std::string indexBottom = char(row + 1) + std::to_string(column);

                Cell *leftCell = _board[indexLeft];
                Cell *rightCell = _board[indexRight];
                Cell *bottomCell = _board[indexBottom];

                _board[index]->setLeftcell(leftCell);
                _board[index]->setRightcell(rightCell);
                _board[index]->setBottomcell(bottomCell);
            }

            if (row == 'g')
            {
                std::string indexLeft = row + std::to_string(column - 1);
                std::string indexRight = row + std::to_string(column + 1);
                std::string indexTop = char(row - 1) + std::to_string(column);

                Cell *leftCell = _board[indexLeft];
                Cell *rightCell = _board[indexRight];
                Cell *topCell = _board[indexTop];

                _board[index]->setLeftcell(leftCell);
                _board[index]->setRightcell(rightCell);
                _board[index]->setTopcell(topCell);
            }

            if (column == 0)
            {
                std::string indexRight = row + std::to_string(column + 1);
                std::string indexTop = char(row - 1) + std::to_string(column);
                std::string indexBottom = char(row + 1) + std::to_string(column);

                Cell *rightCell = _board[indexRight];
                Cell *topCell = _board[indexTop];
                Cell *bottomCell = _board[indexBottom];

                _board[index]->setRightcell(rightCell);
                _board[index]->setTopcell(topCell);
                _board[index]->setBottomcell(bottomCell);
            }

            if (column == 6)
            {
                std::string indexTop = char(row - 1) + std::to_string(column);
                std::string indexBottom = char(row + 1) + std::to_string(column);
                std::string indexLeft = row + std::to_string(column - 1);

                Cell *topCell = _board[indexTop];
                Cell *bottomCell = _board[indexBottom];
                Cell *leftCell = _board[indexLeft];

                _board[index]->setTopcell(topCell);
                _board[index]->setBottomcell(bottomCell);
                _board[index]->setLeftcell(leftCell);
            }

            std::string indexTop = char(row - 1) + std::to_string(column);
            std::string indexBottom = char(row + 1) + std::to_string(column);
            std::string indexLeft = row + std::to_string(column - 1);
            std::string indexRight = row + std::to_string(column + 1);

            Cell *topCell = _board[indexTop];
            Cell *bottomCell = _board[indexBottom];
            Cell *leftCell = _board[indexLeft];
            Cell *rightCell = _board[indexRight];

            _board[index]->setTopcell(topCell);
            _board[index]->setBottomcell(bottomCell);
            _board[index]->setLeftcell(leftCell);
            _board[index]->setRightcell(rightCell);
        }
    }
};

void Board::drawRessource(Ressource *_ressourceRef, std::string *_rarityRef)
{
    *_rarityRef = "";
    *_ressourceRef = undefined;

    std::string listRarity[3] = {"commun", "rare", "épique"};

    while (*_rarityRef == "" && *_ressourceRef == undefined)
    {
        // Choix de la rareté
        std::string selectedRarity = listRarity[rand() % 3];

        // Vérification qu'il existe encore des ressources disponibles
        if (!_map_cases[selectedRarity].empty())
        {

            // Récupération des ressources disponibles
            std::vector<Ressource> availableRessources = {};
            for (const auto &[key, value] : _map_cases[selectedRarity])
            {
                if (value != 0)
                {
                    availableRessources.push_back(key);
                }
            }

            int randomNumber = rand() % availableRessources.size();

            // Choix de la ressource
            Ressource selectedRessource = availableRessources[randomNumber];

            // Décrémentation de la ressource
            _map_cases[selectedRarity][selectedRessource] = _map_cases[selectedRarity][selectedRessource] - 1 ;

            // Suppression si la ressource est égale à 0
            if (_map_cases[selectedRarity][selectedRessource] <= 0)
            {
                _map_cases[selectedRarity].erase(selectedRessource);
            }

            // Attribution aux pointeurs
            *_rarityRef = selectedRarity;
            *_ressourceRef = selectedRessource;
        };
    }
}

Cell* Board::getCellByIndex(std::string index)
{
    return _board[index];
}

void Board::printBoard()
{
    std::cout << "\n";
    
    // on print une ligne horizontale supérieure
    std::cout << "   ";
    for (int column = 0; column < 7; column++) {
        std::cout << " [        " << column << "        ] ";
    }
    std::cout << "\n";
    
    // on print une ligne horizontale supérieure
    std::cout << "   ";
    for (int column = 0; column < 7; column++) {
        std::cout << "---------------------";
    }
    std::cout << "\n";
    
    // On print chaque ligne du plateau
    for (char row = 'a'; row < 'h'; row++)
    {
        std::cout << " " << row << " |"; // On affiche l'étiquette de ligne (a, b, c, ...)
        
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);
            Cell *currentCell = _board[index];
            
            // On récupère les informations de la cellule
            Ressource ressource = currentCell->getCellRessource();
            int diceNumber = currentCell->getCellDiceNumber();
            std::string structureInfo;

            // On check si une ville ou un village est présent
            const City *city = currentCell->getCity();
            if (city != nullptr)
            {
                Player *owner = city->getOwner();
                if (city->getCitySize()== small_town){
                    structureInfo = " 🏘️";
                }else{
                    structureInfo = " 🌇";
                }
                structureInfo += "( " + owner->getName() + " )";
            }
            else
            {
                structureInfo = " ";
            }
            
            // On affiche les informations de la cellule
            std::cout << " [" << ressourceToString(ressource) << ", Dé: " << diceNumber << structureInfo << "] ";
            std::cout << " |";
        }
        std::cout << "\n";
        
        // On print une ligne horizontale après chaque ligne du plateau
        std::cout << "   ";
        for (int column = 0; column < 7; column++) {
            std::cout << "---------------------";
        }
        std::cout << "\n";
    }
}



std::string Board::ressourceToString(Ressource ressource)
{
    switch (ressource)
    {
    case Acier:
        return "Acier 🗼";
    case Bois:
        return "Bois 🪵";
    case Sable:
        return "Sable 🏜️";
    case Ble:
        return "Blé 🌾";
    case Nourriture:
        return "Nourriture 🍛";
    case Pierre:
        return "Pierre 🪨";
    case Argent:
        return "Argent 🥄";
    case Or:
        return "Or 🪙";
    default:
        return "Indéfini";
    }
}

std::vector<Cell*> Board::getCellsbyDiceNumber(int diceNumber){
    std::vector<Cell*> cellsDice;
    for (char row = 'a'; row < 'h'; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);
            if (_board[index]->getCellDiceNumber() == diceNumber){
                cellsDice.push_back(_board[index]);
            }

        }
    }
    return cellsDice;
};