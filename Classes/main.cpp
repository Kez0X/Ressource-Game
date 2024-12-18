#include <iostream>
#include <vector>
#include <random> // Pour générer des nombres aléatoires
#include <string>
#include <ctime>
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include <fstream>
#include "Decks.hpp"

bool isValidIndex(const std::string &chooseIndex)
{
    // Vérification que le format de l'index est correct (2 caractères)
    if (chooseIndex.length() != 2)
    {
        return false;
    }

    // On vérifie que le premier caractère est une lettre entre 'a' et 'g'
    if (chooseIndex[0] < 'a' || chooseIndex[0] > 'g')
    {
        return false;
    }

    // On vérifie que le second caractère est un chiffre entre '0' et '6'
    if (chooseIndex[1] < '0' || chooseIndex[1] > '6')
    {
        return false;
    }

    return true;
}

int main()
{
    // Initialisation des variables du jeu
    int _turn_number = 0;                   // Numéro du tour
    Board *_board = new Board();            // Plateau de jeu
    Decks *_decks = new Decks();            // Paquets de cartes
    srand(std::time(0));                    // Initialisation de la graine
    std::map<std::string, int> _block2_map; // Initialisation de la map d'enregistrement des actions blocages avec l'id de la cellule et le tour d'activation
    // Le tour actuel est : _turn_number

    std::cout << "Lancement de la partie" << "\n"
              << "Création du monde..." << "\n"
              << "Initialisation de l'île..." << "\n\n"
              << "Bon jeu !" << "\n\n" << std::endl;

    // Définition du nombre de joueur entre 2 et 4
    int player_count = 0; // Nombre de joueur
    while (player_count < 2 || player_count > 4)
    {
        std::cout << "Entrez le nombre de joueur souhaités (2-4) : ";
        std::cin >> player_count;
        if (player_count > 4 || player_count < 1){
            std::cout << "Le nombre de joueurs rentré ne respecte pas les règles..." << std::endl;
        }
    }

    // Récupération du nom des joueurs et stockage en mémoire des entités
    Player *players_list[player_count];
    for (int i = 0; i < player_count; i++)
    {
        std::cout << "Entrez le prénom du joueur : ";
        std::string name = "Linus";
        std::cin >> name;
        players_list[i] = new Player(name, 2);
    }

    std::cout << "Lancement du module aléatoire ..." << "\n" << std::endl;

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
    std::cout << "\nTapez 'man' pour connaître les règles (sinon tapez n'importe quoi d'autres) : \n";
    std::cin >> commande;
    if (commande == "man")
    {
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
                  << "Les joueurs peuvent échanger des ressources entre eux ou avec le commerce mondial pendant leur tour.\n" << std::endl;

        // Petite pause avant de passer à la suite
        do
        {
            std::cout << "Tapez 'exit' pour sortir du mode d'emploi \n";
            std::cin >> commande;
        } while (commande != "exit");
    };

    // Placement des villages de chacuns des joueurs dans l'ordre de jeu
    // 2 villages / joueur
    // Cette liste nous servira pour enregistrer les premiers villages placés de chaque joueurs
    std::vector<Cell *> first_towns;
    // On fait 2 tours pour que chaque joueur puisse placer 2 villages
    for (int turns = 0; turns < 2; turns++)
    {
        // Chaque joueur place son village
        for (int i = 0; i < player_count; i++)
        {

            std::cout << "\n-------------------------------------------------------------------------------------------------------\n"
                      << "⭐ Début du jeu ⭐" << "\n"
                      << "Tours n°0" << "\n"
                      << "Joueur : " << players_list[i]->getName() << "\n"
                      << "Vous pouvez placer votre village \n" << std::endl;
            // On affiche le plateau
            _board->printBoard();
            // On initialise les variables de réponses et de vérification
            std::string chooseIndex = "";
            bool placement = false;

            // On demande à l'utilisateur de choisir une case tant que l'index n'est pas valide ou que la case est déjà occupée
            while (!placement)
            {
                std::cout << "Entrez l'id de la case que vous souhaitez prendre (exemple : a1,b2...): ";
                std::cin >> chooseIndex;

                // Vérification de la validité de l'index
                if (isValidIndex(chooseIndex))
                {
                    Cell *chooseCell = _board->getCellByIndex(chooseIndex);

                    // Vérification que la cellule n'est pas déjà occupée par une ville
                    if (chooseCell->getCity() == nullptr)
                    {
                        // Placement du village
                        City *city = new City(players_list[i]);
                        chooseCell->addCity(city);
                        placement = true;

                        if (turns == 0)
                        {
                            // On garde en mémoire le premier village placé
                            first_towns.push_back(chooseCell);
                        }
                    }
                    else
                    {
                        std::cout << "Cette case est déjà occupée par une ville ou un village ! Essayez une autre case.\n" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Index invalide ! Veuillez entrer un index valide (ex: a0, b3, c6,...)\n" << std::endl;
                }
            }
        }
    }

    _board->printBoard();

    // distribution des ressources en fonction du premier village placé et initialisation des scores
    for (int i = 0; i < player_count; i++)
    {
        // Pour chaque cellule adjacente,
        // On récupère les cellules adjacentes
        if (first_towns[i]->getCity() != nullptr)
        {
            first_towns[i]->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(first_towns[i]->getCellRessource()));
        }

        std::vector<Cell *> adjacentCells = {};
        if (first_towns[i]->gettopcell() != nullptr)
        {
            adjacentCells.push_back(first_towns[i]->gettopcell());
        }

        if (first_towns[i]->getleftcell() != nullptr)
        {
            adjacentCells.push_back(first_towns[i]->getleftcell());
        }

        if (first_towns[i]->getrightcell() != nullptr)
        {
            adjacentCells.push_back(first_towns[i]->getrightcell());
        }

        if (first_towns[i]->getbottomcell() != nullptr)
        {
            adjacentCells.push_back(first_towns[i]->getbottomcell());
        }

        // On parcours toutes les cellules adjacentes
        for (int y = 0; y < adjacentCells.size(); y++)
        {
            Cell *_cell = adjacentCells[y];
            // On check si la cellule est valide
            // On récupère la ressource de la cellule
            Ressource ressource_card = _cell->getCellRessource();

            // On donne une carte de cette ressource au propriétaire de la ville
            City *_city = first_towns[i]->getCity();
            Player *_owner = _city->getOwner();
            Card _cardToADD = _decks->drawCardFromRessourceDeck(ressource_card);
            _owner->addCard(_cardToADD);
        }
    }

    std::cout << "\n🎮 Début du jeu 🎮\n" << std::endl;

    // commencement du jeu
    int player_turn = 0;
    int number_turns = 1;
    while (players_list[player_turn]->getScore() < 20)
    {
        // Définition du joueur du tour
        Player *currentPlayer = players_list[player_turn];

        // Décrémentation des effets des cellules et des bonus des joueurs
        for (char row = 'a'; row < 'h'; row++)
        {
            for (int column = 0; column < 7; column++)
            {
                std::string index = row + std::to_string(column);
                Cell *_cell = _board->getCellByIndex(index);
                if (_cell->getEffectRemainingTime() > 0)
                {
                    _cell->setEffectRemainingTime(_cell->getEffectRemainingTime() - 1);
                }
                else if (_cell->getEffectRemainingTime() == 0)
                {
                    _cell->setStateNormal();
                }
            }
        }
        if (currentPlayer->getBonus() > 0)
        {
            currentPlayer->setBonus(currentPlayer->getBonus() - 1);
        }

        std::vector<Cell *> Cell_list_dice = {};
        int random_number = -1;
        while (Cell_list_dice.size() == 0)
        {
            random_number = (rand() % 12) + 1;
            Cell_list_dice = _board->getCellsbyDiceNumber(random_number);
        }

        _board->printBoard();

        std::cout << "\n"
                  << "=============================\n"
                  << "Tour n°" << number_turns << " \n";
        std::cout << "Joueur " << players_list[player_turn]->getName() << " à vous de jouer ! \n\n";
        std::cout << "Lancement des dés 🎲🎲 \n"
                  << "Le nombre lancé est : " << random_number << "\n\n" << std::endl;
        std::cout << "Voici la liste des cases concernés par le lancement du tirage : " << std::endl;

        // Générer la liste des cases concernés par le tirage (id des cellules ayant le numéro du dé contenu)
        std::string response = "";
        for (int i = 0; i < Cell_list_dice.size(); i++)
        {
            std::cout << "- Numéro de cellule : " << Cell_list_dice[i]->getCellID() << std::endl;

            // On parcours toutes les cellules adjacentes
            std::vector<Cell *> adjacentCells = {};
            if (Cell_list_dice[i]->gettopcell() != nullptr)
            {
                adjacentCells.push_back(Cell_list_dice[i]->gettopcell());
            }

            if (Cell_list_dice[i]->getleftcell() != nullptr)
            {
                adjacentCells.push_back(Cell_list_dice[i]->getleftcell());
            }

            if (Cell_list_dice[i]->getrightcell() != nullptr)
            {
                adjacentCells.push_back(Cell_list_dice[i]->getrightcell());
            }

            if (Cell_list_dice[i]->getbottomcell() != nullptr)
            {
                adjacentCells.push_back(Cell_list_dice[i]->getbottomcell());
            }

            adjacentCells.push_back(Cell_list_dice[i]);

            // Une fois qu'on a les id vérifier les villages adjacent et ceux des cellules pour vérifier si il y en a
            // Si un village est adjacent ou sur une cellule ,dont le numéro du dé a été tiré au sort, alors on donne la ressource présente sur la cellule
            //,dont le numéro du dé a été tiré au sort, au joueur propriétaire du village (pas uniquement au joueur qui a son tour en cours)
            for (int y = 0; y < adjacentCells.size(); y++)
            {
                Cell *_cell = adjacentCells[y];

                if (_cell->getCity() != nullptr)
                {

                    // On verifie les bonus
                    if (_cell->getState() == blocked)
                    {
                        std::cout << "La cellule " << _cell->getCellID() << " a été bloquée, les ressources ne seront donc pas distribuées aux joueurs adjacents." << std::endl;
                    }
                    else if (_cell->getCity()->getOwner()->getBonus() > 0)
                    {
                        std::cout << "Ressource attribué en double" << std::endl;
                        _cell->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(Cell_list_dice[i]->getCellRessource()));
                        _cell->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(Cell_list_dice[i]->getCellRessource()));
                    }
                    else
                    {
                        _cell->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(Cell_list_dice[i]->getCellRessource()));
                    }
                }
            }
        }

        // Déroulement d'un tour
        do
        {
            // Possibilité durant tout le tour de proposer des échanges avec d'autres joueurs / le commerce mondial
            std::cout << "\nVoici la liste des actions que vous pouvez faire : \n"
                      << "1. Echange avec d'autres joueurs ou avec le commerce mondiale : /echange \n"
                      << "2. Jouer une ou plusieurs de vos cartes bonus : /play-bonus \n"
                      << "3. Construire un village : /build \n"
                      << "4. Améliorer un village en ville : /level-up \n"
                      << "5. Construire une/plusieurs carte(s) bonus : /build-bonus \n"
                      << "6. Consulter votre deck : /deck \n"
                      << "7. Consulter votre nombre de points : /score \n"
                      << "8. Consulter les règles : /man \n"
                      << "9. Afficher le plateau : /board \n"
                      << "10. Mettre fin à votre tour : /end \n\n"
                      << "Rentrez votre commande : ";
            std::cin >> response;

            if (response == "/echange")
            {
                // Sélectionner le type de carte à échanger
                std::string resType = "";
                while (!(resType == "bonus" || resType == "ressource"))
                {
                    std::cout << "Quel type de carte souhaitez-vous échanger (ressource/bonus) ? ";
                    std::cin >> resType;
                }
                TypeCard tradeCardType = (resType == "bonus") ? bonus : ressource;
                std::cout << ">" << tradeCardType << " sélectionné" << std::endl;

                // Sélectionner les cartes disponibles pour échange
                std::vector<Card> availableForTrade = players_list[player_turn]->getDeckFilter(tradeCardType);

                if (availableForTrade.empty())
                {
                    std::cout << "AUCUNE CARTE DISPONIBLE À L'ÉCHANGE DANS VOTRE DECK POUR CETTE CATÉGORIE." << std::endl;
                }
                else
                {
                    // Choisir avec qui échanger
                    std::string exchangePerson = "";
                    while (!(exchangePerson == "monde" || exchangePerson == "joueur"))
                    {
                        std::cout << "Avec qui souhaitez-vous échanger ? (monde/joueur) : ";
                        std::cin >> exchangePerson;
                    }

                    if (exchangePerson == "monde")
                    {
                        // Échange avec le commerce mondial
                        std::cout << "Votre deck (4 ressources identiques nécessaires) :" << std::endl;
                        std::map<std::string, int> cardCount;
                        for (Card &card : availableForTrade)
                        {
                            cardCount[card.getTitre()]++;
                        }

                        // Afficher les cartes ayant au moins 4 exemplaires
                        bool hasFour = false;
                        for (const auto &pair : cardCount)
                        {
                            if (pair.second >= 4)
                            {
                                hasFour = true;
                                std::cout << "- " << pair.first << " (" << pair.second << " disponibles)" << std::endl;
                            }
                        }

                        if (!hasFour)
                        {
                            std::cout << "Vous n'avez pas 4 cartes identiques pour un échange avec le monde." << std::endl;
                        }
                        else
                        {
                            // Sélection d'une carte à échanger
                            std::string chosenCard = "";
                            while (cardCount[chosenCard] < 4)
                            {
                                std::cout << "Entrez le titre de la carte que vous voulez échanger (4 identiques) : ";
                                std::cin >> chosenCard;
                            }

                            // Effectuer l'échange
                            for (int i = 0, count = 0; i < currentPlayer->getDeck().size() && count < 4; ++i)
                            {
                                if (currentPlayer->getDeck()[i].getTitre() == chosenCard)
                                {
                                    currentPlayer->getDeck().erase(currentPlayer->getDeck().begin() + i);
                                    --i;
                                    ++count;
                                }
                            }
                            Card newCard = _decks->drawCardFromRessourceDeck(undefined);
                            currentPlayer->getDeck().push_back(newCard);
                            std::cout << "Vous avez obtenu : " << newCard.getTitre() << std::endl;
                        }
                    }
                    else
                    {
                        // Échange avec un joueur
                        std::cout << "Joueurs ouverts à l'échange :" << std::endl;
                        std::vector<Player *> exchangeOpenPlayers;
                        for (int i = 0; i < player_count; i++)
                        {
                            if (!(players_list[i]->getDeck().empty() || players_list[i] == currentPlayer))
                            {
                                exchangeOpenPlayers.push_back(players_list[i]);
                                std::cout << exchangeOpenPlayers.size() - 1 << ": " << players_list[i]->getName() << " ("
                                          << players_list[i]->getDeck().size() << " cartes dans son deck)" << std::endl;
                            }
                        }

                        if (exchangeOpenPlayers.empty())
                        {
                            std::cout << "AUCUN JOUEUR NE PEUT ÉCHANGER AVEC VOUS." << std::endl;
                        }
                        else
                        {
                            // Sélection d'un joueur
                            int playerChoice = -1;
                            while (playerChoice < 0 || playerChoice >= exchangeOpenPlayers.size())
                            {
                                std::cout << "Choisissez le joueur avec qui échanger (numéro) : ";
                                std::cin >> playerChoice;
                            }
                            Player *selectedTradePlayer = exchangeOpenPlayers[playerChoice];
                            std::cout << "> " << selectedTradePlayer->getName() << " sélectionné." << std::endl;

                            // Proposer des cartes à échanger
                            std::cout << "Choisissez les cartes que vous souhaitez proposer pour échange : " << std::endl;
                            std::vector<Card> currentDeck = currentPlayer->getDeck();
                            for (int i = 0; i < currentDeck.size(); i++)
                            {
                                std::cout << i << ": " << currentDeck[i].getTitre() << " (" << currentDeck[i].getRarete() << ")" << std::endl;
                            }

                            std::vector<int> proposedCardsIndices;
                            int cardIndex = 0;
                            std::cout << "Entrez les indices des cartes que vous voulez proposer (tapez -1 pour terminer) : ";
                            while (true)
                            {
                                std::cin >> cardIndex;
                                if (cardIndex == -1)
                                    break;
                                if (cardIndex >= 0 && cardIndex < currentDeck.size())
                                {
                                    proposedCardsIndices.push_back(cardIndex);
                                }
                                else
                                {
                                    std::cout << "Indice invalide, réessayez." << std::endl;
                                }
                            }

                            // Afficher les cartes proposées
                            std::cout << "Vous proposez :" << std::endl;
                            for (int index : proposedCardsIndices)
                            {
                                std::cout << "- " << currentDeck[index].getTitre() << std::endl;
                            }

                            // Demander les cartes de l'adversaire
                            std::cout << selectedTradePlayer->getName() << " deck - Choisissez les cartes que vous souhaiteriez recevoir en échnage des cartes proposées : " << std::endl;
                            std::vector<Card> opponentDeck = selectedTradePlayer->getDeck();
                            for (int i = 0; i < opponentDeck.size(); i++)
                            {
                                std::cout << i << ": " << opponentDeck[i].getTitre() << " (" << opponentDeck[i].getRarete() << ")" << std::endl;
                            }

                            std::vector<int> requestedCardsIndices;
                            cardIndex = 0;
                            std::cout << "Entrez les indices des cartes que vous voulez demander (tapez -1 pour terminer) : ";
                            while (true)
                            {
                                std::cin >> cardIndex;
                                if (cardIndex == -1)
                                    break;
                                if (cardIndex >= 0 && cardIndex < opponentDeck.size())
                                {
                                    requestedCardsIndices.push_back(cardIndex);
                                }
                                else
                                {
                                    std::cout << "Indice invalide, réessayez." << std::endl;
                                }
                            }

                            // Afficher les cartes demandées
                            std::cout << "Vous demandez :" << std::endl;
                            for (int index : requestedCardsIndices)
                            {
                                std::cout << "- " << opponentDeck[index].getTitre() << std::endl;
                            }

                            // Demander à l'adversaire d'accepter ou refuser
                            std::cout << selectedTradePlayer->getName() << ", acceptez-vous cet échange ? (oui/non) : ";
                            std::string response;
                            std::cin >> response;

                            if (response == "oui")
                            {
                                // Effectuer l'échange
                                std::vector<Card> newDeckCurrentPlayer = currentPlayer->getDeck();
                                std::vector<Card> newDeckOpponent = selectedTradePlayer->getDeck();

                                // Retirer les cartes proposées et ajout à l'adversaire
                                for (int index : proposedCardsIndices)
                                {
                                    newDeckOpponent.push_back(currentDeck[index]);
                                }

                                // Retirer les cartes demandées et ajout au joueur actuel
                                for (int index : requestedCardsIndices)
                                {
                                    newDeckCurrentPlayer.push_back(opponentDeck[index]);
                                }

                                // Mise à jour des decks
                                for (int i = proposedCardsIndices.size() - 1; i >= 0; --i)
                                {
                                    newDeckCurrentPlayer.erase(newDeckCurrentPlayer.begin() + proposedCardsIndices[i]);
                                }
                                for (int i = requestedCardsIndices.size() - 1; i >= 0; --i)
                                {
                                    newDeckOpponent.erase(newDeckOpponent.begin() + requestedCardsIndices[i]);
                                }

                                currentPlayer->setDeck(newDeckCurrentPlayer);
                                selectedTradePlayer->setDeck(newDeckOpponent);

                                std::cout << "Échange effectué !" << std::endl;
                            }
                            else
                            {
                                std::cout << selectedTradePlayer->getName() << " a refusé l'échange." << std::endl;
                            }
                        }
                    }
                }
            }

            else if (response == "/play-bonus")
            {
                // Montrer les différentes cartes bonus
                // Vérifier si le joueur a des cartes bonus disponibles
                std::vector<Card> bonusCards = players_list[player_turn]->getDeckFilter(bonus);
                if (bonusCards.empty())
                {
                    std::cout << "Vous n'avez aucune carte bonus à jouer." << std::endl;
                }
                else
                {
                    std::cout << players_list[player_turn]->getName() << " - votre deck :" << std::endl;
                    for (int i = 0; i < bonusCards.size(); i++)
                    {
                        std::cout << i << ": " << bonusCards[i].getTitre() << " (" << bonusCards[i].getRarete() << ")\n"
                                  << "Description : " << bonusCards[i].getDesc() << std::endl;
                    }

                    // Demander au joueur de choisir une carte bonus à jouer
                    int selectedBonus = -1;
                    while (selectedBonus < 0 || selectedBonus >= bonusCards.size())
                    {
                        std::cout << "Entrez le numéro de la carte bonus que vous souhaitez jouer : ";
                        std::cin >> selectedBonus;

                        if (selectedBonus < 0 || selectedBonus >= bonusCards.size())
                        {
                            std::cout << "Numéro invalide, veuillez réessayer." << std::endl;
                        }
                    }

                    // Vérifier l'état de la carte et lancer l'effet si elle peut être utilisée
                    Card &chosenCard = bonusCards[selectedBonus];
                    if (chosenCard.getStatus() == NotUse)
                    {
                        std::cout << "Vous jouez la carte bonus : " << chosenCard.getTitre() << std::endl;
                        // Lancer l'effet de la carte
                        if (chosenCard.getType() == ressource)
                        {
                            std::cout << "Cette commande est impossible sur une carte ressource" << std::endl;
                        }
                        else
                        {
                            if (chosenCard.getId() == "stoleACardToAPlayer")
                            {
                                std::cout << "Effet activé : Voler une carte à un joueur.\n";
                                chosenCard.setAlreadyUseStatus();
                                // Implémentation pour voler une carte à un joueur
                                // Exemple : demander au joueur de choisir un adversaire et une carte ressource à voler
                                std::cout << "Voici la liste des joueurs : " << std::endl;
                                for (int i = 0; i < player_count; i++)
                                {
                                    std::cout << std::to_string(i + 1) << ". " << players_list[i]->getName();
                                }
                                int targetPlayer;
                                do
                                {
                                    std::cout << "Choisissez un joueur chez qui voler une carte : " << std::endl;
                                    std::cin >> targetPlayer;
                                } while (players_list[targetPlayer - 1]->getName() == players_list[player_turn]->getName());
                                if (players_list[targetPlayer - 1]->getDeck().size() == 0)
                                {
                                    std::cout << "Vous avez mal choisi, le joueur désigné n'a plus de cartes..." << std::endl;
                                }
                                else
                                {
                                    std::vector<Card> targetDeck = players_list[targetPlayer - 1]->getDeck();
                                    if (!targetDeck.empty())
                                    {
                                        Card targetCard = targetDeck[targetDeck.size() - 1];
                                        targetDeck.pop_back();
                                        players_list[player_turn]->addCard(targetCard);
                                        std::cout << "Le vol a bien été effectué !" << std::endl;
                                    }
                                    std::cout << "Vous avez mal choisi, le joueur désigné n'a plus de cartes..." << std::endl;
                                }
                            }
                            else if (chosenCard.getId() == "doubleRessourcesDuringOneTurn")
                            {
                                std::cout << "Effet activé : Doubler les ressources pendant un tour.\n";
                                // Implémentation pour doubler les ressources du joueur pendant un tour
                                players_list[player_turn]->setBonus(players_list[player_turn]->getBonus() + 1);
                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "BlockCellDuringTwoTurn")
                            {
                                std::cout << "Effet activé : Bloquer une cellule pendant deux tours.\n";
                                // Implémentation pour bloquer une cellule ressource pendant 2 tours
                                _board->printBoard();
                                std::string chooseIndex = "";
                                chosenCard.setAlreadyUseStatus();
                                do
                                {
                                    std::cout << "Selectionnez la cellule que vous souhaitez bloquer : ";
                                    std::cin >> chooseIndex;
                                } while (!isValidIndex(chooseIndex));
                                Cell *_cell = _board->getCellByIndex(chooseIndex);
                                _cell->setStateBlocked();
                                _cell->setEffectRemainingTime(2);
                                std::cout << "La cellule choisie a bien été bloquée" << std::endl;
                                // On enregistre la cellule qui a été bloqué avec le tour
                            }
                            else if (chosenCard.getId() == "stoleACardToAllPlayers")
                            {
                                std::cout << "Effet activé : Voler une carte à tous les joueurs.\n";
                                // Implémentation pour voler une carte à tous les joueurs
                                for (int i = 0; i < player_count; i++)
                                {
                                    if (i != player_turn)
                                    {
                                        std::vector<Card> targetDeck = players_list[i]->getDeck();
                                        if (!targetDeck.empty())
                                        {
                                            Card targetCard = targetDeck[targetDeck.size() - 1];
                                            targetDeck.pop_back();
                                            players_list[player_turn]->addCard(targetCard);
                                            std::cout << "Le vol a bien été effectué sur " << players_list[i]->getName() << std::endl;
                                        }
                                        else
                                        {
                                            std::cout << players_list[i]->getName() << " n'a pas de cartes... " << std::endl;
                                        }
                                    }
                                }
                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "doubleRessourcesDuringThreeTurns")
                            {
                                std::cout << "Effet activé : Doubler les ressources pendant trois tours.\n";
                                // Implémentation pour doubler les ressources du joueur pendant 3 tours
                                players_list[player_turn]->setBonus(players_list[player_turn]->getBonus() + 3);

                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "BlockCellDuringFiveTurns")
                            {
                                std::cout << "Effet activé : Bloquer une cellule pendant cinq tours.\n";
                                // Implémentation pour bloquer une cellule ressource pendant 2 tours
                                _board->printBoard();
                                std::string chooseIndex = "";
                                chosenCard.setAlreadyUseStatus();
                                do
                                {
                                    std::cout << "Selectionnez la cellule que vous souhaitez bloquer : ";
                                    std::cin >> chooseIndex;
                                } while (!isValidIndex(chooseIndex));
                                Cell *_cell = _board->getCellByIndex(chooseIndex);
                                _cell->setStateBlocked();
                                _cell->setEffectRemainingTime(5);
                                std::cout << "La cellule choisie a bien été bloquée" << std::endl;
                                // On enregistre la cellule qui a été bloqué avec le tour
                            }
                            else if (chosenCard.getId() == "WinOnePoint")
                            {
                                std::cout << "Effet activé : Gagner un point.\n";
                                int _score = currentPlayer->getScore() + 1;
                                currentPlayer->setScore(_score);
                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "WinThreePoints")
                            {
                                std::cout << "Effet activé : Gagner trois points.\n";
                                int _score = currentPlayer->getScore() + 3;
                                currentPlayer->setScore(_score);
                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "stoleARessourceToAllPlayers")
                            {
                                std::cout << "Effet activé : Voler une ressource à tous les joueurs.\n";

                                std::string query = "";
                                Ressource selectedRessource = undefined;
                                bool ressourceSelected = false;
                                while (ressourceSelected)
                                {
                                    if (query == "Acier")
                                    {
                                        std::cout << "Vous avez sélectionné : Acier.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Acier;
                                    }
                                    else if (query == "Bois")
                                    {
                                        std::cout << "Vous avez sélectionné : Bois.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Bois;
                                    }
                                    else if (query == "Sable")
                                    {
                                        std::cout << "Vous avez sélectionné : Sable.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Sable;
                                    }
                                    else if (query == "Pierre")
                                    {
                                        std::cout << "Vous avez sélectionné : Pierre.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Pierre;
                                    }
                                    else if (query == "Or")
                                    {
                                        std::cout << "Vous avez sélectionné : Or.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Or;
                                    }
                                    else if (query == "Blé")
                                    {
                                        std::cout << "Vous avez sélectionné : Blé.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Ble;
                                    }
                                    else if (query == "Argent")
                                    {
                                        std::cout << "Vous avez sélectionné : Argent.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Argent;
                                    }
                                    else if (query == "Nourriture")
                                    {
                                        std::cout << "Vous avez sélectionné : Nourriture.\n";
                                        ressourceSelected = true;
                                        selectedRessource = Nourriture;
                                    }
                                    else
                                    {
                                        std::cout << "Ressource invalide, veuillez réessayer.\n";
                                    }

                                    // Demander la saisie de l'utilisateur
                                    std::cout << "Entrez la ressource à voler (Acier/Bois/Sable/Pierre/Or/Blé/Argent/Nourriture) : ";
                                    std::cin >> query;
                                }

                                for (int i = 0; i < player_count; i++)
                                {
                                    if (i != player_turn)
                                    {
                                        std::vector<Card> targetDeck = players_list[i]->getDeck();
                                        if (!targetDeck.empty())
                                        {
                                            std::vector<Card> _newDeck;
                                            for (int y = 0; y < targetDeck.size(); y++)
                                            {
                                                Card _card = targetDeck[y];
                                                if (_card.getTitre() == query)
                                                {
                                                    currentPlayer->addCard(_card);
                                                }
                                                else
                                                {
                                                    _newDeck.push_back(_card);
                                                }
                                            }
                                            std::cout << "Le vol a bien été effectué sur " << players_list[i]->getName() << std::endl;
                                            players_list[i]->setDeck(_newDeck);
                                        }
                                        else
                                        {
                                            std::cout << players_list[i]->getName() << " n'a pas de cartes de cette ressource... " << std::endl;
                                        }
                                    }
                                }

                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "DestroyASmallTown")
                            {
                                std::cout << "Effet activé : Détruire un village.\n";
                                int chooseTown = 0;
                                _board->printBoard();
                                std::vector<Cell *> listCities = _board->getTowns();
                                // On affiche les villes et leurs propriétaires
                                for (int i = 0; i < listCities.size(); i++)
                                {
                                    std::cout << i + 1 << ". Village de " << listCities[i]->getCity()->getOwner()->getName() << " : case " << listCities[i]->getCellID() << std::endl;
                                }
                                do
                                {
                                    std::cout << "Choisissez le village que vous souhaitez détruire : ";
                                    std::cin >> chooseTown;
                                } while (chooseTown < 1 && chooseTown > listCities.size());
                                std::cout << "\nDestruction du village en cours...\n";
                                listCities[chooseTown - 1]->setCityToDestroy();
                                int newScore = listCities[chooseTown -1]->getCity()->getOwner()->getScore() -1;
                                listCities[chooseTown -1]->getCity()->getOwner()->setScore(newScore);
                                delete listCities[chooseTown -1];
                                std::cout << "Village détruit !" << std::endl;
                                chosenCard.setAlreadyUseStatus();
                            }
                            else if (chosenCard.getId() == "BlockACityDuringFourTurns")
                            {
                                std::cout << "Effet activé : Bloquer une ville pendant quatre tours.\n";
                                // Implémentation pour bloquer une cellule ressource pendant 2 tours
                                _board->printBoard();
                                std::string chooseIndex = "";
                                chosenCard.setAlreadyUseStatus();
                                do
                                {
                                    std::cout << "Selectionnez la cellule que vous souhaitez bloquer : ";
                                    std::cin >> chooseIndex;
                                } while (!isValidIndex(chooseIndex));
                                Cell *_cell = _board->getCellByIndex(chooseIndex);
                                _cell->setStateBlocked();
                                _cell->setEffectRemainingTime(4);
                                std::cout << "La cellule choisie a bien été bloquée" << std::endl;
                                // On enregistre la cellule qui a été bloqué avec le tour
                            }
                            else if (chosenCard.getId() == "DestroyRessource")
                            {
                                std::cout << "Effet activé : Détruire une ressource.\n";
                                _board->printBoard();
                                std::string choice = "";
                                bool valid = false;
                                std::cout << "\nChoisissez une case ressource à détruire. Attention, vous n'avez pas le droit de sélectionner une case sur laquelle il y a un village ou une ville. \n";
                                do
                                {
                                    std::cout << "Rentrez votre choix : ";
                                    std::cin >> choice;
                                    if (isValidIndex(choice))
                                    {
                                        if (_board->getCellByIndex(choice)->getCity() == nullptr)
                                        {
                                            valid = true;
                                        }
                                    }
                                } while (valid != true);
                                _board->getCellByIndex(choice)->setRessourceDestroy();
                                chosenCard.setAlreadyUseStatus();
                            }
                            else
                            {
                                std::cout << "Effet inconnu. Aucune action n'a été exécutée.\n";
                            }
                        }

                        // Mettre à jour le statut de la carte
                        chosenCard.setStatus(Using);
                    }
                    else if (chosenCard.getStatus() == Using)
                    {
                        std::cout << "Cette carte est déjà en cours d'utilisation." << std::endl;
                    }
                    else
                    {
                        std::cout << "Cette carte a déjà été utilisée." << std::endl;
                    }
                }
            }
            else if (response == "/build")
            {
                // Montrer le coût d'un village
                std::cout << "COUT D'UN VILLAGE " << std::endl;
                std::cout << "4 bois (pour les fondations) – 2 Sable (Pour les vitres) – 2 Blé (Pour la toiture) – 1 Nourriture (Pour les habitants)" << std::endl;

                // Montrer le deck du joueur
                currentPlayer->printDeck();

                // Montrer le plateau si besoin
                std::cout << "Visualiser le plateau ? (oui/non) : ";
                std::string response = "";
                std::cin >> response;
                if (response == "oui")
                {
                    _board->printBoard();
                }
                response = "";
                std::cout << "Souhaitez vous continuer la construction du village ? (oui/non) : ";
                std::cin >> response;
                if (response == "oui"){
                    // Demander confirmation de la construction ainsi que la case visée
                bool available = false;
                Cell *cell = nullptr;
                while (!available)
                {
                    std::string casequery = "";
                    std::cout << "Donnez l'id de la case ou vous souhaitez construire : ";
                    std::cin >> casequery;

                    cell = _board->getCellByIndex(casequery);

                    if (cell == nullptr)
                    {
                        std::cout << "Cette case n'existe pas." << std::endl;
                        available = false;
                    }
                    else if (cell->getState() != normal)
                    {
                        std::cout << "Cette case a été détruite ou est bloquée." << std::endl;
                        available = false;
                    }
                    else if (cell->getCity() != nullptr)
                    {
                        std::cout << "Une ville existe déjà sur cette case." << std::endl;
                        available = false;
                    }
                    else
                    {
                        available = true;
                    }
                }

                if (available)
                {
                    // vérification des ressources
                    bool enoughRessources = false;
                    int bois, sable, nourriture, ble = 0;
                    for (int i = 0; i < currentPlayer->getDeck().size(); i++)
                    {
                        Card _card = currentPlayer->getDeck()[i];
                        if (_card.getTitre() == "Bois")
                        {
                            bois++;
                        }
                        else if (_card.getTitre() == "Sable")
                        {
                            sable++;
                        }
                        else if (_card.getTitre() == "Blé")
                        {
                            ble++;
                        }
                        else if (_card.getTitre() == "Nourriture")
                        {
                            nourriture++;
                        }
                    }
                    if (bois >= 4 && sable >= 2 && ble >= 2 && nourriture >= 1)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires";
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires";
                    }

                    // Construire le village
                    if (enoughRessources)
                    {
                        cell->addCity(new City(currentPlayer, small_town));
                        int newScore = currentPlayer->getScore()+1;
                        // On incrémente le nouveau score
                        currentPlayer->setScore(newScore);
                        std::cout << "Village construit." << std::endl;
                    }
                }
            }else{
                std::cout << "\nContruction annulée\n" << std::endl;
            }
            }
            else if (response == "/level-up")
            {
                // Montrer le coût d'une ville
                std::cout << "COUT D'UNE VILLE " << std::endl;
                std::cout << "3 Acier (pour les fondations) – 3 Sable (Pour les vitres) – 2 Pierre (Pour les routes) – 5 Nourriture (pour les habitants) – 6 bois (Pour les poutres et fondations)" << std::endl;

                // Montrer le deck du joueur
                currentPlayer->printDeck();

                // Montrer le plateau si besoin
                std::cout << "Visualiser le plateau ? (oui/non) : ";
                std::string response = "";
                std::cin >> response;
                if (response == "oui")
                {
                    _board->printBoard();
                }

                // Demander confirmation de l'amélioration ainsi que la case visée
                bool available = false;
                Cell *cell = nullptr;
                while (!available)
                {
                    std::string casequery = "";
                    std::cout << "Donnez l'id de la case ou le village que vous souhaitez améliorer se trouve : ";
                    std::cin >> casequery;

                    cell = _board->getCellByIndex(casequery);

                    if (cell == nullptr)
                    {
                        std::cout << "Cette case n'existe pas." << std::endl;
                        available = false;
                    }
                    else if (cell->getState() != normal)
                    {
                        std::cout << "Cette case a été détruite ou est bloquée." << std::endl;
                        available = false;
                    }
                    else if (cell->getCity() == nullptr)
                    {
                        std::cout << "Aucun village n'existe sur cette case." << std::endl;
                        available = false;
                    }
                    else if (cell->getCity()->getOwner() != currentPlayer)
                    {
                        std::cout << "Le village de cette case ne vous appartient pas." << std::endl;
                        available = false;
                    }
                    else
                    {
                        available = true;
                    }
                }

                // Vérifier que la construction est possible (un village du joueur est déjà présent sur la case et l'utiliasteur possède les ressources nécessaires)
                if (available)
                {
                    // vérification des ressources
                    bool enoughRessources = false;
                    int acier, bois, sable, nourriture, pierre = 0;
                    for (int i = 0; i < currentPlayer->getDeck().size(); i++)
                    {
                        Card _card = currentPlayer->getDeck()[i];
                        if (_card.getTitre() == "Bois")
                        {
                            bois++;
                        }
                        else if (_card.getTitre() == "Sable")
                        {
                            sable++;
                        }
                        else if (_card.getTitre() == "Bois")
                        {
                            bois++;
                        }
                        else if (_card.getTitre() == "Nourriture")
                        {
                            nourriture++;
                        }
                        else if (_card.getTitre() == "Pierre")
                        {
                            pierre++;
                        }
                    }
                    if (acier >= 3 && sable >= 3 && pierre >= 2 && nourriture >= 5 && bois >= 6)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires";
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires";
                    }

                    // Construire le village
                    if (enoughRessources)
                    {
                        cell->getCity()->setTownToCity();
                        int initialScore = cell->getCity()->getOwner()->getScore();
                        cell->getCity()->getOwner()->setScore(initialScore+1);
                        std::cout << "Village amélioré en ville." << std::endl;
                    }
                }

                // Améliorer le village en ville
            }
            else if (response == "/build-bonus")
            {
                // Montrer le coût des cartes bonus
                std::cout << "COUT DES CARTES BONUS" << std::endl;
                std::cout << "- Carte bonus commune : 2 Acier – 5 Bois – 2 Sable – 1 Pierre – 3 Nourriture \n- Carte bonus rare : 4 Acier – 5 Bois – 3 Pierre – 4 Nourriture – 4 Blé – 5 Sable\n- Carte bonus épique : 1 Or – 2 Argent – 5 Bois – 5 Acier – 5 Nourriture – 4 Blé" << std::endl;

                // Montrer le deck du joueur
                currentPlayer->printDeck();

                // Demander la rareté de la carte voulu
                std::string rarity = "Default";
                while (rarity != "commun" && rarity != "rare" && rarity != "epique")
                {
                    std::cout << "Sélectionnez la rareté voulue (commun/rare/epique): ";
                    std::cin >> rarity;
                }

                bool enoughRessources = false;
                int acier, bois, sable, pierre, nourriture, gold, ble, argent = 0;
                for (int i = 0; i < currentPlayer->getDeck().size(); i++)
                {
                    Card _card = currentPlayer->getDeck()[i];
                    if (_card.getTitre() == "Acier")
                    {
                        acier++;
                    }
                    else if (_card.getTitre() == "Bois")
                    {
                        bois++;
                    }
                    else if (_card.getTitre() == "Sable")
                    {
                        sable++;
                    }
                    else if (_card.getTitre() == "Blé")
                    {
                        ble++;
                    }
                    else if (_card.getTitre() == "Nourriture")
                    {
                        nourriture++;
                    }
                    else if (_card.getTitre() == "Pierre")
                    {
                        pierre++;
                    }
                    else if (_card.getTitre() == "Argent")
                    {
                        argent++;
                    }
                    else if (_card.getTitre() == "Or")
                    {
                        gold++;
                    }
                    // Carte default non supporté ou bonus
                }

                // Vérification des ressources
                if (rarity == "epique")
                {
                    // epique
                    if (gold >= 1 && argent >= 2 && bois >= 5 && acier >= 5 && nourriture >= 5 && ble >= 4)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires";
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires";
                    }
                }
                else if (rarity == "rare")
                {
                    // rare
                    if (acier >= 4 && bois >= 5 && pierre >= 3 && nourriture >= 4 && ble >= 4 && sable >= 5)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires" << std::endl;
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires" << std::endl;
                    }
                }
                else
                {
                    // commun
                    if (acier >= 2 && bois >= 5 && sable >= 2 && pierre >= 1 && nourriture >= 3)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires" << std::endl;
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires" << std::endl;
                    }
                }

                if (enoughRessources)
                {
                    // Pioche de la carte bonus avec la rareté correspondante
                    Card createdBonusCard = _decks->drawCardFromBonusDeck(rarity);

                    // Affichage de la carte avec sa description
                    std::cout << createdBonusCard.getTitre() << std::endl
                              << createdBonusCard.getDesc() << std::endl;
                }
            }
            else if (response == "/deck")
            {
                // Affiche le deck du joueur methode printdeck dans Player
                players_list[player_turn]->printDeck();
            }
            else if (response == "/score")
            {
                // Affiche le score du player
                std::cout << std::to_string(players_list[player_turn]->getScore());
            }
            else if (response == "/man")
            {
                // Affiche les règles du jeu
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
            }
            else if (response == "/end")
            {
                std::cout << "Vous avez décidé de mettre fin à votre tour : " << players_list[player_turn]->getName() << "\n\n"
                          << "=======================================\n";
                break;
            }else if (response == "/board"){
                _board->printBoard();
            }
            else
            {
                std::cout << "La commande rentrée n'existe pas, veuillez rééssayer ! \n";
            }

            std::cout << std::endl
                      << "> Retour au menu principal <" << std::endl;
        } while (response != "/end");

        if (player_turn == player_count - 1)
        {
            player_turn = 0;
            number_turns++;
        }
        else
        {
            player_turn++;
        }
    }
    std::cout << "\n\n=====================================\n\n🏆Nous avons un gagnant !🏆\nFélications " << players_list[player_turn]->getName() << ", tu as gagné ! \n\n=====================================";
    std::cout << "Voici les scores : " << std::endl;
    for (int i = 0; i < player_count; i++)
    {
        std::cout << players_list[i]->getName() << " : " << players_list[i]->getScore() << std::endl;
    }

    // Suppression des variables en mémoire
    for (char row = 'a'; row < 'h'; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            std::string index = row + std::to_string(column);
            if (_board->getCellByIndex(index)->getCity() != nullptr)
            {
                delete _board->getCellByIndex(index)->getCity();
            }
            delete _board->getCellByIndex(index);
        }
    }

    delete _decks;

    for (int i = 0; i < player_count; i++)
    {
        delete players_list[i];
    }

    std::cout << "\nMerci d'avoir joué !\n"
              << std::endl;

    return 0;
};