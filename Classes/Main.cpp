#include <iostream>
#include <vector>
#include <random> // Pour générer des nombres aléatoires
#include <string>
#include <ctime>
#include "Board.hpp"
#include "Player.hpp"
#include <fstream>
#include "Decks.hpp"

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
    srand(std::time(0)); // Initialisation de la graine

    std::cout << "Lancement de la partie" << "\n" << "Création du monde..." << "\n" << "Initialisation de l'île..." << "\n\n" << "Bon jeu !" << "\n\n";

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
        std::cout << "Entrez le prénom du joueur : ";
        std::string name = "Linus";
        std::cin >> name;
        players_list[i] = new Player(name);
    }

    std::cout << "Lancement du module aléatoire ..." << "\n";

    // Définition de l'ordre de jeu
    for (int i = 0; i < player_count; i++)
    {
        int random_number = rand() % player_count;
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

    std::string commande;
    std::cout << "Tapez 'man' pour connaître les règles : \n";
    std::cin >> commande;
    if(commande == "man"){
        std::cout << "## Ressource-Game - Règles du jeu\n\n"
          << "### Synopsis :\n"
          << "Ressource-Game est un jeu de stratégie en C++ inspiré du jeu *Catane*. L'objectif est de construire des villages et des villes à l'aide de ressources. L'emplacement de vos villages et villes déterminera les ressources disponibles. Les villes doublent les ressources récupérées.\n\n"
          
          << "### Ressources disponibles :\n"
          << "Les ressources nécessaires à la construction des villages et des villes sont les suivantes :\n"
          << "- **Acier**\n"
          << "- **Bois**\n"
          << "- **Sable**\n"
          << "- **Pierre**\n"
          << "- **Or**\n"
          << "- **Blé**\n"
          << "- **Argent**\n"
          << "- **Nourriture**\n\n"

          << "Chaque ressource est répartie sur 48 cases, classées en fonction de leur rareté :\n"
          << "- **Acier** (6 cases) - Commun\n"
          << "- **Bois** (10 cases) - Commun\n"
          << "- **Sable** (9 cases) - Commun\n"
          << "- **Pierre** (4 cases) - Rare\n"
          << "- **Or** (1 case) - Épique\n"
          << "- **Blé** (9 cases) - Commun\n"
          << "- **Argent** (2 cases) - Épique\n"
          << "- **Nourriture** (8 cases) - Commun\n\n"

          << "### Objectif du jeu :\n"
          << "Le but est d’atteindre 20 points :\n"
          << "- **Village** = 1 point (accède aux ressources adjacentes)\n"
          << "- **Ville** = 2 points (accède au double des ressources)\n\n"

          << "### Construction :\n"
          << "Pour construire des villages et des villes, vous devez accumuler les ressources suivantes :\n\n"
          
          << "**Village** :\n"
          << "- 4 Bois (fondations)\n"
          << "- 2 Sable (vitres)\n"
          << "- 2 Blé (toiture)\n"
          << "- 1 Nourriture (habitants)\n\n"

          << "**Ville** :\n"
          << "- 3 Acier (fondations)\n"
          << "- 3 Sable (vitres)\n"
          << "- 2 Pierre (routes)\n"
          << "- 5 Nourriture (habitants)\n"
          << "- 6 Bois (poutres)\n\n"

          << "### Cartes Bonus :\n"
          << "Les cartes bonus sont classées en 3 catégories (commune, rare, épique). Voici quelques exemples :\n\n"
          
          << "**Carte bonus commune** (45 cartes) :\n"
          << "- Voler 1 carte à un joueur\n"
          << "- Doubler les ressources pendant 1 tour\n"
          << "- Bloquer une case ressource pendant 2 tours\n\n"

          << "**Carte bonus rare** (20 cartes) :\n"
          << "- Voler 1 carte à chaque joueur\n"
          << "- Doubler les ressources pendant 3 tours\n"
          << "- Gagner 1 point\n\n"

          << "**Carte bonus épique** (15 cartes) :\n"
          << "- Voler toutes les cartes d’une ressource chez chaque joueur\n"
          << "- Détruire un village adverse\n"
          << "- Assiéger une ville (elle ne peut pas être utilisée pendant 4 tours)\n"
          << "- Gagner 3 points\n"
          << "- Annihiler une ressource pour le reste de la partie\n\n"

          << "### Nombre de joueurs :\n"
          << "De 2 à 4 joueurs\n\n"

          << "### Début de la partie :\n"
          << "Chaque joueur place 2 villages sur le plateau, l’ordre de jeu est déterminé aléatoirement. Après placement, chaque joueur reçoit une ressource de chaque case adjacente au premier village.\n\n"

          << "### Déroulement d'un tour :\n"
          << "1. **Carte bonus** : Le joueur peut jouer une carte bonus de son deck.\n"
          << "2. **Lancer des dés** : Chaque joueur reçoit les ressources correspondant aux numéros tirés sur les cases adjacentes à ses villages/ villes.\n"
          << "3. **Construction** : Le joueur peut construire des villages, des villes ou des cartes bonus. Il peut également proposer des échanges avec d'autres joueurs ou utiliser le commerce mondial (4 ressources identiques contre 1 différente).\n\n"

          << "### Échanges :\n"
          << "Les joueurs peuvent échanger des ressources entre eux ou avec le commerce mondial pendant leur tour.\n";

        // Petite pause avant de passer à la suite
        do{
        std::cout << "Tapez 'exit' pour sortir du mode d'emploi \n";
        std::cin >> commande;
        }while(commande!="exit");
    };

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
            
            std::cout << "\n-------------------------------------------------------------------------------------------------------\n" << "Début du jeu : " << "\n" << "Tours n°" << std::to_string(turns) << "\n" << "Joueur : " << players_list[i]->getName() << "\n";
            // On affiche le plateau
            _board->printBoard();
            // On initialise les variables de réponses et de vérification
            std::string chooseIndex = "";
            bool placement = false;
            
            // On demande à l'utilisateur de choisir une case tant que l'index n'est pas valide ou que la case est déjà occupée
            while (!placement) {
                std::cout << "Entrez l'id de la case que vous souhaitez prendre : ";
                std::cin >> chooseIndex;

                // Vérification de la validité de l'index
                if (isValidIndex(chooseIndex)) {
                    Cell *chooseCell = _board->getCellByIndex(chooseIndex);

                    // Vérification que la cellule n'est pas déjà occupée par une ville
                    if (chooseCell->getCity() == nullptr) {
                        // Placement du village
                        City *city = new City(players_list[i]);
                        chooseCell->addCity(city);
                        placement = true;

                        if (turns == 0) {
                            // On garde en mémoire le premier village placé
                            first_towns.push_back(chooseCell);
                        }
                    } else {
                        std::cout << "Cette case est déjà occupée par une ville ou un village ! Essayez une autre case.\n";
                    }
                } else {
                    std::cout << "Index invalide ! Veuillez entrer un index valide (ex: a0, b3, c6,...)\n";
                }
            }
        }
    }

    _board->printBoard();
    // distribution des ressources en fonction du premier village placé et initialisation des scores
    for (int i = 0; i < player_count; i++) {
        players_list[i]->setScore(2);
        // On récupère les cellules adjacentes
        Cell* adjacent_cells[] = {
            first_towns[i]->gettopcell(),
            first_towns[i]->getleftcell(),
            first_towns[i]->getrightcell(),
            first_towns[i]->getbottomcell(),
        };

        // On parcours toutes les cellules adjacentes
        for (Cell* cell : adjacent_cells) {
            if (cell != nullptr) { // On check si la cellule est valide
                // On récupère la ressource de la cellule
                Ressource ressource_card = cell->getCellRessource();
                
                // On donne une carte de cette ressource au propriétaire de la ville
                first_towns[i]->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(ressource_card)
                );
            }
        }
        first_towns[i]->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(first_towns[i]->getCellRessource()));
    }

    // commencement du jeu
    int player_turn = 0;
    int number_turns = 1;
    while(players_list[player_turn]->getScore() < 20){
        std::string reponse;
        int random_number = rand() % 12;
        std::cout << "Tour n°" << std::to_string(number_turns) <<" \n";
        std::cout << "Joueur " << players_list[player_turn]->getName() << " à vous de jouer ! \n\n";
        std::cout << "Lancement des dés 🎲🎲 \n" << "Le nombre lancé est : " << std::to_string(random_number) << "\n" << "Processing..." << "\n" << "Processing..." << "\n" << "Processing..."
        << "Voici la liste des cases concernés par le lancement du tirage : \n\n";

        // Générer la liste des cases concernés par le tirage (id des cellules ayant le numéro du dé contenu)
        // Une fois qu'on a les id vérifier les villages adjacent et ceux des cellules pour vérifier si il y en a 
        // Si un village est adjacent ou sur une cellule ,dont le numéro du dé a été tiré au sort, alors on donne la ressource présente sur la cellule 
        //,dont le numéro du dé a été tiré au sort, au joueur propriétaire du village (pas uniquement au joueur qui a son tour en cours)
        
        // Déroulement d'un tour
        do{
        std::string reponse = "";
        // Possibilité durant tout le tour de proposer des échanges avec d'autres joueurs / le commerce mondial
        std::cout << "Voici la liste des actions que vous pouvez faire : \n" 
        << "1. Echange avec d'autres joueurs ou avec le commerce mondiale : /echange \n" 
        << "2. Jouer une ou plusieurs de vos cartes bonus : /play-bonus \n" 
        << "3. Construire un village : /build \n" 
        << "4. Améliorer un village en ville : /level-up \n"
        << "5. Construire une/plusieurs carte(s) bonus : /build-bonus \n"
        << "6. Consulter votre deck : /deck \n"
        << "7. Consulter votre nombre de points : /score \n"
        << "8. Consulter les règles : /man \n"
        << "9. Mettre fin à votre tour : /end \n"
        << "Rentrez votre commande : " << std::endl;
        std::cin >> reponse;

        if (reponse == "/echange"){
            // Proposez les différents échanges possible monde ou avec les autres joueurs et développer l'interface 
        }
        else if (reponse == "/play-bonus"){
            // Montrer les différentes cartes bonus
            // Demander laquelle jouer
            // Lancer l'effet si la carte n'est pas en cours d'utilisation, ni déjà utilisé
        }
        else if (reponse == "/build"){
            // Montrer le coût d'un village
            // Montrer le deck du joueur
            // Demander confirmation de la construction ainsi que la case visée
            // Vérifier que la construction est possible (pas de villes déjà présente et l'utiliasteur possède les ressources nécessaires)
            // Construire le village
        }
        else if (reponse == "/level-up"){
            // Montrer le coût d'une ville
            // Montrer le deck du joueur
            // Demander confirmation de la construction ainsi que la case visée (proposer les cases ayant déjà les villages de l'utilisateur)
            // Vérifier que la construction est possible (un village du joueur est déjà présent sur la case et l'utiliasteur possède les ressources nécessaires)
            // Améliorer le village en ville
        }
        else if (reponse == "/build-bonus"){
            // Montrer le coût des cartes bonus
            // Montrer le deck du joueur
            // Demander la rareté de la carte voulu
            // Vérification des ressources
            // Pioche de la carte bonus avec la rareté correspondante
            // Affichage de la carte avec sa description
        }
        else if (reponse == "/deck"){
            // Affiche le deck du joueur methode printdeck dans Player
            players_list[player_turn]->printDeck();
        }
        else if (reponse == "/score"){
            // Affiche le score du player
            std::cout << std::to_string(players_list[player_turn]->getScore());
        }
        else if (reponse == "/man"){
            // Affiche les règles du jeu
        }
        else if (reponse == "/end"){
            std::cout << "Vous avez décidé de mettre fin à votre tour : " << players_list[player_turn]->getName() << "\n\n" << "=======================================\n";
            break;
        }
        else {
            std::cout << "La commande rentrée n'existe pas, veuillez rééssayer ! \n";
        }
        }while(reponse != "/end");


        if (player_turn == player_count-1){
            player_turn = 0;
            number_turns++;
        }else{
            player_turn++;
        }
    }

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