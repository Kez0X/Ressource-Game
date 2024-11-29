#include <iostream>
#include <vector>
#include <algorithm> // Pour std::shuffle
#include <random>    // Pour générer des nombres aléatoires
//#include "Board.h"
//#include "Player.h"

namespace Game {

    class Game {
    private:
        int _turn_number = 0;           // Numéro du tour actuel
        int _current_turn = 0;          // Index du joueur en cours
        Board _board;                   // Instance du plateau
        std::vector<Player> _players;   // Liste des joueurs

    public:
        // Constructeur
        Game(std::vector<Player> players) : _players(players) {}

        // Méthode pour initialiser le jeu
        void initialize_game() {
            std::cout << "Bienvenue dans le jeu de stratégie !\n";

            // Étape 1 : Choisir le nombre de joueurs (entre 2 et 4)
            int num_players = 0;
            while (num_players < 2 || num_players > 4) {
                std::cout << "Entrez le nombre de joueurs (2-4) : ";
                std::cin >> num_players;
                if (num_players < 2 || num_players > 4) {
                    std::cout << "Nombre de joueurs invalide. Réessayez.\n";
                }
            }

            // Création des joueurs
            for (int i = 0; i < num_players; ++i) {
                std::string name;
                std::cout << "Entrez le nom du joueur " << i + 1 << ": ";
                std::cin >> name;
                _players.emplace_back(Player(name));
            }

            // Étape 2 : Générer le plateau avec les ressources et les chiffres aléatoires
            std::cout << "Génération du plateau...\n";
            _board.initialize_board();

            // Étape 3 : Déterminer l'ordre de jeu des joueurs aléatoirement
            determine_turn_order();

            // Étape 4 : Placement des villages par les joueurs
            std::cout << "Placement des villages initiaux...\n";
            place_initial_villages();

            // Étape 5 : Distribution des ressources adjacentes au premier village
            std::cout << "Distribution des ressources initiales...\n";
            distribute_initial_resources();

            // Étape 6 : Prêt à jouer
            std::cout << "Le jeu est prêt à commencer !\n";
        }

        // Détermine l'ordre de jeu aléatoirement
        void determine_turn_order() {
            std::random_device rd; // Générateur d'entropie
            std::mt19937 gen(rd());
            std::vector<int> rolls;

            for (auto& player : _players) {
                int roll1 = std::uniform_int_distribution<>(1, 6)(gen);
                int roll2 = std::uniform_int_distribution<>(1, 6)(gen);
                int total = roll1 + roll2;
                rolls.push_back(total);
                std::cout << player.get_name() << " a lancé " << roll1 << " + " << roll2 << " = " << total << "\n";
            }

            // Trier les joueurs par leur score au lancer de dés
            std::sort(_players.begin(), _players.end(), [&](Player& a, Player& b) {
                return a.get_dice_roll() > b.get_dice_roll();
            });

            std::cout << "Ordre de jeu déterminé :\n";
            for (size_t i = 0; i < _players.size(); ++i) {
                std::cout << "Joueur " << i + 1 << ": " << _players[i].get_name() << "\n";
            }
        }

        // Placement des villages initiaux
        void place_initial_villages() {
            for (int round = 0; round < 2; ++round) { // Chaque joueur place 2 villages
                for (auto& player : _players) {
                    _board.display(); // Afficher l'état actuel du plateau
                    std::cout << player.get_name() << ", entrez les coordonnées pour placer votre village (x y) : ";
                    int x, y;
                    std::cin >> x >> y;

                    while (!_board.place_village(player, x, y)) {
                        std::cout << "Position invalide. Réessayez : ";
                        std::cin >> x >> y;
                    }
                }
            }
        }

        // Distribution des ressources initiales
        void distribute_initial_resources() {
            for (auto& player : _players) {
                std::vector<Case> adjacent_cases = _board.get_adjacent_cases(player.get_first_village_position());
                for (const auto& case : adjacent_cases) {
                    player.add_resource(case.get_resource_type(), 1); // 1 unité par case adjacente
                }
                std::cout << player.get_name() << " a reçu ses ressources initiales.\n";
            }
        }
    };
}
