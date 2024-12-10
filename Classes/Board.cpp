#include "Board.hpp"
#include "Cell.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <random>
#include <ctime>
#include <vector>

Board::Board(){
    _map_cases = {{"commun", {{Acier, 6},{Bois , 10}, {Sable , 9}, {Ble , 9}, {Nourriture, 8}}},{"rare" , {{Pierre , 4}}}, {"épique", {{Argent,2}, {Or , 1}}}};
    _map_dice = {{"commun" , {5,6,7,8,9}}, {"rare", {3,4,10,11}}, {"épique" , {1,2,12}}};

    int column = 0;
    char row = 'a';

    std::string index = row + std::to_string(column);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // Tirage de la ressource aléatoire
            Ressource* cellRessource = new Ressource;
            std::string* cellRarity = new std::string;
            drawRessource(cellRessource, cellRarity);

            // Choix du numéro du dés
            int cellDiceNumber = _map_dice[*cellRarity][randomInt() % _map_dice[*cellRarity].size()];

            // Génération de la cellule
            _board[index] = new Cell(index, *cellRessource, cellDiceNumber, normal);

            delete cellRessource;
            delete cellRarity;
            column++;
        }
        column = 0;
        row++;
    }
};

int randomInt() 
{
    std::srand(std::time(0));
    return std::rand();
}

void Board::drawRessource(Ressource* _ressourceRef, std::string* _rarityRef) {
    *_rarityRef = "";
    *_ressourceRef = undefined;

    std::string listRarity[3] = {"commun", "rare", "épique"};

    while (*_rarityRef == "" && *_ressourceRef == undefined)
    {
        // Choix de la rareté
        std::string selectedRarity = listRarity[randomInt() % 3];
        
        // Vérification qu'il existe encore des ressources disponibles
        if (!_map_cases[selectedRarity].empty()) {

            // Récupération des ressources disponibles
            std::vector<Ressource> availableRessources = {};
            for (const auto& [key, value] : _map_cases[selectedRarity]) {
                if (value!= 0){
                    availableRessources.push_back(key);
                }
            }

            // Choix de la ressource
            Ressource selectedRessource = availableRessources[randomInt() % availableRessources.size()];

            // Décrémentation de la ressource
            _map_cases[selectedRarity][selectedRessource]--;

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