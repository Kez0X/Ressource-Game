#include <iostream>
#include <vector>
#include <algorithm> // Pour std::shuffle
#include <random>    // Pour générer des nombres aléatoires
#include <string>
#include <Board.hpp>
#include <Player.hpp>

void main()
{

    // Initialisation des variables du jeu
    int _turn_number = 0;        // Numéro du tour
    Board* _board = new Board(); // Plateau de jeu

    // Définition du nombre de joueur entre 2 et 4
    int player_count = 0; // Nombre de joueur
    while (player_count < 2 && player_count > 4)
    {
        std::cout << "Entrez le nombre de joueur souhaités (2-4) : ";
        std::cin >> player_count;
    }

    // Récupération du nom des joueurs et stockage en mémoire des entités
    Player* players_list[player_count]; 
    for (int i = 0; i < player_count; i++)
    {
        std::cout << "Entrez le prénom du joueur ";
        players_list[i] = new Player();
    }

    // Suppression des variables en mémoire
    delete _board;
    for (int i = 0; i < player_count; i++)
    {
        delete players_list[i];
    }
    
};