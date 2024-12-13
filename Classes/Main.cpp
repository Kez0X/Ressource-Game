#include <iostream>
#include <vector>
#include <random> // Pour générer des nombres aléatoires
#include <string>
#include <ctime>
#include "Board.hpp"
#include "Player.hpp"
#include <fstream>
#include "Decks.hpp"

int randomInt()
{
    std::srand(std::time(0));
    return std::rand();
}

bool isValidIndex(const std::string& chooseIndex) {
    // Vérification que le format de l'index est correct (2 caractères)
    if (chooseIndex.length() != 2) {
        return false;
    }

    // On vérifie que le premier caractère est une lettre entre 'a' et 'g'
    if (chooseIndex[0] < 'a' || chooseIndex[0] > 'g') {
        return false;
    }

    // On vérifie que le second caractère est un chiffre entre '0' et '6'
    if (chooseIndex[1] < '0' || chooseIndex[1] > '6') {
        return false;
    }

    return true;
}

int main()
{
    // Initialisation des variables du jeu
    int _turn_number = 0;        // Numéro du tour
    Board *_board = new Board(); // Plateau de jeu
    Decks *_decks = new Decks(); // Paquets de cartes

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
    // Cette liste nous servira pour enregistrer les premiers villages placés de chaque joueurs
    std::vector<Cell*> first_towns;
    // On fait 2 tours pour que chaque joueur puisse placer 2 villages
    for (int turns = 0; turns < 2; turns++)
    {
        // Chaque joueur place son village
        for (int i = 0; i < player_count; i++)
        {
            // On affiche le plateau
            _board->printBoard();
            // On initialise les variables de réponses et de vérification
            std::string chooseIndex = "";
            bool placement = false;
            // On verifie bien que les données rentrée par l'utilisateur sont cohérentes
            while (!isValidIndex(chooseIndex) && placement!=true){
                std::cout << "Entrez l'id de la case que vous souhaitez prendre : ";
                std::cin >> chooseIndex;
                // Si c'est ok alors on peut placer le village
                if(isValidIndex(chooseIndex)){
                    Cell * chooseCell = _board->getCellByIndex(chooseIndex);
                    // On regarde si une ville est déjà présente
                    if (chooseCell->getCity() != nullptr){
                        // Si ce n'est pas le cas alors on peut sortir de la boucle
                        placement = true;
                        // Et placer la ville
                        City * city = new City(players_list[i]);
                        chooseCell->addCity(city);
                        if (turns ==0){
                            // On garde en mémoire le premier village placer - pour faciliter la suite on enregistre directement la cellule du village
                            first_towns.push_back(chooseCell);
                        }
                    }
                }
            }
        }
    }

    // distribution des ressources en fonction du premier village placé
     for (int i = 0; i < player_count; i++)
    {
        // On vérifie qu'on n'est pas sur un des bords du plateau
        if (first_towns[i]->getleftcell() != nullptr){
            // On récupère la ressource
            Ressource ressource_card = first_towns[i]->getleftcell()->getCellRessource();
            // Une fois la ressource récupéré on récupère la carte du paquet correspondant

        }
    }


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

    delete _decks;

    for (int i = 0; i < player_count; i++)
    {
        delete players_list[i];
    }

    return 0;
};