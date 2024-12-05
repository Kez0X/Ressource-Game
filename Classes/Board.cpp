#include "Board.hpp"
#include "Cell.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <random>
#include <ctime>

Board::Board(){
    std::map<std::string, std::map<std::string, int>> map_cases = {{"commun", {{"Acier", 5},{"Bois" , 10}, {"Sable" , 7}, {"Blé" , 7}, {"Nourriture", 8}}},{"rare" , {{"Pierre" , 4}}}, {"épique", {{"Argent",2}, {"Or" , 1}}}};
    std::map<std::string, std::vector<int>> map_dice = {{"commun" , {5,6,7,8,9}}, {"rare", {3,4,10,11}}, {"épique" , {1,2,12}}};
};

/* -	Acier (5 cases – classe : commun)
-	Bois (10 cases – classe : commun)
-	Sable (7 cases – classe : commun)
-	Pierre (4 cases – classe : rare)
-	Or (1 case – classe : épique)
-	Blé (7 cases – classe : commun)
-	Argent (2 cases – classe : épique)
-	Nourriture (8 cases – classe : commun)
*
commun : 5-6-7-8-9
rare : 3-4 - 10 - 11
épique : 1- 2 - 12
 */


void boardCreation(std::map<std::string, std::map<std::string, int>> map_cases, std::map<std::string, std::vector<int>> map_dice, Cell cell, int id){
    Cell* topcell = cell.gettopcell();
    Cell* rightcell = cell.getrightcell();
    Cell* leftcell = cell.getleftcell();
    Cell* bottomcell = cell.getbottomcell();
    if (topcell == nullptr && leftcell == nullptr){
        std::vector<std::string> ressources = ressourceAlea(map_cases); // On a récupérer la ressource aléatoire et sa classe
        Ressource ressourceSelect = ressources[0];
        std::srand(std::time(0));
        int randomNumber = 1 + std::rand() % map_dice[ressources[1]].size();
        int diceNumber = map_dice[ressources[1]][randomNumber-1];

        Cell newCell = Cell(id, ressources[0], diceNumber, normal,  Cell* , Cell* , Cell* , Cell* ); // On creer la nouvelle cellule
        map_cases[ressources[1]][ressources[0]] -=1;
        if (verfifyDicoEmpty(map_cases[ressources[1]])){
            map_cases[ressources[1]] = {};
        }
    }
}

bool verfifyDicoEmpty(std::map<std::string, int> map){
    bool rep = true;
    for (const auto& [key, value] : map) {
            if (value != 0){
                rep = false;
            }
        }
    return rep;
}


std::vector<std::string> ressourceAlea(std::map<std::string, std::map<std::string, int>> map_cases){
    std::srand(std::time(0));
    std::vector<std::string> listOfKeys;
    std::string ressourceChoice = "";
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
    return {ressourceChoice, classe};
}