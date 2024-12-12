#include <iostream>
#include <vector>
#include <random> // Pour générer des nombres aléatoires
#include <string>
#include <ctime>

#include "Board.hpp"
#include "Player.hpp"

int randomInt()
{
    std::srand(std::time(0));
    return std::rand();
}

int main()
{

    // Initialisation des variables du jeu
    int _turn_number = 0;        // Numéro du tour
    Board *_board = new Board(); // Plateau de jeu

    // Définition du nombre de joueur entre 2 et 4
    int player_count = 0; // Nombre de joueur
    while (player_count < 2 || player_count > 4)
    {
        std::cout << "Entrez le nombre de joueur souhaités (2-4) : ";
        std::cin >> player_count;
    }

    // Récupération du nom des joueurs et stockage en mémoire des entités
    Player *players_list[player_count];
    for (int i = 0; i < player_count; i++)
    {
        std::cout << "Entrez le prénom du joueur ";
        std::string name = "Linus";
        std::cin >> name;
        players_list[i] = new Player(name);
    }

    // Définition de l'ordre de jeu
    for (int i = 0; i < player_count; i++)
    {
        int random_number = randomInt() % player_count;
        Player *swap = players_list[i];
        players_list[i] = players_list[random_number];
        players_list[random_number] = swap;
    }
    std::cout << std::endl
              << "Voici l'ordre de jeu" << std::endl;
    for (int i = 0; i < player_count; i++)
    {
        std::cout << i << ". " << players_list[i]->getName() << std::endl;
    }

    // Placement des villages de chacuns des joueurs dans l'ordre de jeu
    // 2 villages / joueur
    int i = 0;
    while(i<8){
        // On affiche le plateau

        i++;
    }

    // On garde en mémoire le permier village placer



    // distribution des ressources en fonction du premier village placé


    // commencement du jeu

        // Déroulement d'un tour

        // Possibilité durant tout le tour de proposer des échanges avec d'autres joueurs / le commerce mondial

        // Possibilité de jouer des cartes BONUS

        // Lancement des dés et distributions des ressources en fonction du placement des villages / villes

        // Possibilité de construire un village / améliorer un village en ville / construire une ou plusieurs cartes bonus

        // Fin du tour

    // Le jeu d'arrête quand un joueur arrive à 20 points

    // Suppression des variables en mémoire
    for (char row = 'a'; row < 'h'; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);
            delete _board->getCellByIndex(index);
        }
    }

    for (int i = 0; i < player_count; i++)
    {
        delete players_list[i];
    }

    return 0;
};