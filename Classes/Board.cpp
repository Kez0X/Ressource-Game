#include "Board.hpp"
#include "Cell.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <random>
#include <ctime>

Board::Board(){
    std::map<std::string, std::map<Ressource, int>> map_cases = {{"commun", {{Acier, 5},{Bois , 10}, {Sable , 7}, {Ble , 7}, {Nourriture, 8}}},{"rare" , {{Pierre , 4}}}, {"épique", {{Argent,2}, {Or , 1}}}};
    std::map<std::string, std::vector<int>> map_dice = {{"commun" , {5,6,7,8,9}}, {"rare", {3,4,10,11}}, {"épique" , {1,2,12}}};
};


Cell boardCreation(std::map<std::string, std::map<Ressource, int>> map_cases, std::map<std::string, std::vector<int>> map_dice, Cell cell, int id){
    Cell* topcell = cell.gettopcell();
    Cell* rightcell = cell.getrightcell();
    Cell* leftcell = cell.getleftcell();
    Cell* bottomcell = cell.getbottomcell();
    // Si tout les pointeurs sont nulls alors c'est notre 1 ère itération
    // Ici on a les pointeurs de la cellule parente

    Cell* newTopcell = nullptr;
    Cell* newRightcell = nullptr;
    Cell* newLeftcell = nullptr;
    Cell* newBottomcell = nullptr;
    // Ici on a les pointeurs de la nouvelle cellule
    // Quand on creer un nouvelle cellule on estime qu'elle est seule
    // On génère toutes les informations nécessaires à la création de la cellule
    std::vector<Ressource, std::string> ressources = ressourceAlea(map_cases); // On a récupérer la ressource aléatoire et sa classe
    Ressource ressourceSelect = ressources[0];
    std::srand(std::time(0));
    int randomNumber = 1 + std::rand() % map_dice[ressources[1]].size();
    int diceNumber = map_dice[ressources[1]][randomNumber-1];
    // On creer notre cellule
    Cell newCell = Cell(id, ressources[0], diceNumber, normal, newTopcell , newRightcell , newLeftcell , newBottomcell ); // On creer la nouvelle cellule
    // On fait les mises à jour necessaires dans le dictionnaire
    map_cases[ressources[1]][ressources[0]] -=1;
    if (verfifyDicoEmpty(map_cases[ressources[1]])){
        map_cases[ressources[1]] = {};
    }

    if (id == 44){
        // Il faut lier les pointeurs entre eux
        return newCell;
    }else{

        if (topcell == nullptr && leftcell == nullptr && rightcell == nullptr && bottomcell == nullptr){ // C'est le cas en haut à gauche du plateau
            // On part du postula que la cellule parente vient de droite
            cell.setLeftcell(&newCell);
            newCell.setRightcell(&cell);
            id +=1;
            // On n'a plus qu'à définir la cellule du bas
            newCell.setBottomcell(boardCreation(map_cases, map_dice, newCell, id));
        } // Puis les autres cas...
}

bool verfifyDicoEmpty(std::map<Ressource, int> map){
    bool rep = true;
    for (const auto& [key, value] : map) {
            if (value != 0){
                rep = false;
            }
        }
    return rep;
}


std::vector<Ressource, std::string> ressourceAlea(std::map<std::string, std::map<Ressource, int>> map_cases){
    std::srand(std::time(0));
    std::vector<Ressource> listOfKeys;
    Ressource ressourceChoice;
    std::string classe = "";
    int randomNumber = 1 + std::rand() % 3;
    if (randomNumber==1 && !map_cases["commun"].empty()){
        for (const auto& [key, value] : map_cases["commun"]) {
            if (value!= 0){
                listOfKeys.push_back(key);
            }
        }
        std::srand(std::time(0));
        int SecondRandomNumber = 1 + std::rand() % listOfKeys.size();
        ressourceChoice = listOfKeys[SecondRandomNumber-1];
        classe = "commun";
        // On a la ressource aléatoirement choisi parmi celles restantes
    }else if (randomNumber==2 && !map_cases["rare"].empty()){
        for (const auto& [key, value] : map_cases["rare"]) {
            if (value!= 0){
                listOfKeys.push_back(key);
            }
        }
        std::srand(std::time(0));
        int SecondRandomNumber = 1 + std::rand() % listOfKeys.size();
        ressourceChoice = listOfKeys[SecondRandomNumber-1];
        classe = "rare";
        // On a la ressource aléatoirement choisi parmi celles restantes
    }else if (randomNumber==3 && !map_cases["épique"].empty()){
        for (const auto& [key, value] : map_cases["épique"]) {
            if (value!= 0){
                listOfKeys.push_back(key);
            }
        }
        std::srand(std::time(0));
        int SecondRandomNumber = 1 + std::rand() % listOfKeys.size();
        ressourceChoice = listOfKeys[SecondRandomNumber-1];
        classe = "épique";
        // On a la ressource aléatoirement choisi parmi celles restantes
    }
    std::vector<Ressource, std::string> listElt = {ressourceChoice, classe};
    return listElt;
}