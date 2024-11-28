#include <iostream>
#include <vector>
#include <algorithm> // Pour std::shuffle :)
#include <random>
//#include "Board.h" // à définir on preshot
//#include "Player.h" // à définir on preshot

namespace Game {

    class Game {
    private:
        int _turn_number = 0;           // Numéro du tour actuel
        int _current_turn = 0;          // Index du joueur en cours
        int nb_joueur = 0;              // Le nombre de joueurs
        std::string surname;            // Le nom des joueurs
        Board _board;                   // Instance du plateau de jeu
        std::vector<Player> _players;   // Liste des joueurs

    public:
        Game(std::vector<Player> players) : _players(players) {
           // Le plateau a déjà été défini dans les private avec la disposition des ressources...etc...
           // Donc on commence par déterminer combien de joueurs vont jouer ?
           do
           {
            std::cout << "Rentrer le nombre de joueur souhaité (Entre 1 et 4)\n";
            std::cin >> nb_joueur;
           } while (1>nb_joueur && nb_joueur>4);
            // Ensuite il faut qu'on demande à tous les utilisateurs leurs noms
            for (int i = 0; i < nb_joueur; i++)
            {
                std::cout << "Joueur " << i << " - Veuillez rentrer votre surnom : ";
                std::cin >> surname;
                _players.push_back()
            }
            


            std::cout << "Détermination de l'ordre des joueurs...\n";
            determine_turn_order();

            // Étape 3 : Placement des villages initiaux
            std::cout << "Placement des villages initiaux...\n";
            place_initial_villages();

            std::cout << "Le jeu est prêt à commencer !\n";
        }

        // Méthode pour déterminer l'ordre de jeu aléatoirement
        void determine_turn_order() {
            std::random_device rd; // Source d'entropie
            std::mt19937 g(rd()); // Générateur pseudo-aléatoire
            std::shuffle(_players.begin(), _players.end(), g);

            std::cout << "Ordre des joueurs :\n";
            for (size_t i = 0; i < _players.size(); i++) {
                std::cout << "Joueur " << i + 1 << ": " << _players[i].get_name() << "\n";
            }
        }

        // Méthode pour placer les villages initiaux
        void place_initial_villages() {
            for (int round = 0; round < 2; ++round) { // Chaque joueur place 2 villages
                for (auto &player : _players) {
                    std::cout << player.get_name() << ", placez votre village :\n";
                    _board.place_village(player);
                    // Distribution des ressources adjacentes
                    std::cout << "Distribution des ressources adjacentes...\n";
                    _board.distribute_initial_resources(player);
                }
            }
        }

        // Méthode pour jouer un tour
        void play_turn() {
            Player& current_player = _players[_current_turn];
            std::cout << "C'est au tour de " << current_player.get_name() << " !\n";

            // Étape 1 : Utilisation optionnelle d'une carte bonus
            current_player.use_bonus_card();

            // Étape 2 : Lancer les dés
            int dice_roll = roll_dice();
            std::cout << "Résultat du lancer de dés : " << dice_roll << "\n";

            // Étape 3 : Distribution des ressources
            _board.distribute_resources(dice_roll);

            // Étape 4 : Actions du joueur (échanges, construction, etc.)
            current_player.perform_actions(_board);

            // Étape 5 : Passer au joueur suivant
            _current_turn = (_current_turn + 1) % _players.size();
            _turn_number++;
        }

        // Méthode pour vérifier si un joueur a atteint la condition de victoire
        bool check_end_condition() {
            for (const auto& player : _players) {
                if (player.get_points() >= 20) {
                    std::cout << player.get_name() << " a gagné la partie avec " << player.get_points() << " points !\n";
                    return true;
                }
            }
            return false;
        }

        // Méthode pour lancer les dés
        int roll_dice() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, 6);
            return distrib(gen) + distrib(gen); // Deux dés à 6 faces
        }
    };
}
