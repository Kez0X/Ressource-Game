#include "Board.hpp"
#include "Cell.hpp"
#include <iostream>
#include <cassert>
#include <map>

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

Cell* boardCreation(std::map<std::string, std::map<std::string, int>> map, Cell* board){
    // 
}