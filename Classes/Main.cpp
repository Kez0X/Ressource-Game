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
    int _turn_number = 0;        // Numéro du tour
    Board *_board = new Board(); // Plateau de jeu
    Decks *_decks = new Decks(); // Paquets de cartes
    srand(std::time(0));         // Initialisation de la graine

    std::cout << "Lancement de la partie" << "\n"
              << "Création du monde..." << "\n"
              << "Initialisation de l'île..." << "\n\n"
              << "Bon jeu !" << "\n\n";

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
                  << "Les joueurs peuvent échanger des ressources entre eux ou avec le commerce mondial pendant leur tour.\n";

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
                      << "Début du jeu : " << "\n"
                      << "Tours n°" << std::to_string(turns) << "\n"
                      << "Joueur : " << players_list[i]->getName() << "\n";
            // On affiche le plateau
            _board->printBoard();
            // On initialise les variables de réponses et de vérification
            std::string chooseIndex = "";
            bool placement = false;

            // On demande à l'utilisateur de choisir une case tant que l'index n'est pas valide ou que la case est déjà occupée
            while (!placement)
            {
                std::cout << "Entrez l'id de la case que vous souhaitez prendre : ";
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
                        std::cout << "Cette case est déjà occupée par une ville ou un village ! Essayez une autre case.\n";
                    }
                }
                else
                {
                    std::cout << "Index invalide ! Veuillez entrer un index valide (ex: a0, b3, c6,...)\n";
                }
            }
        }
    }

    _board->printBoard();
    // distribution des ressources en fonction du premier village placé et initialisation des scores
    for (int i = 0; i < player_count; i++)
    {
        players_list[i]->setScore(2);
        // On récupère les cellules adjacentes
        Cell *adjacent_cells[] = {
            first_towns[i]->gettopcell(),
            first_towns[i]->getleftcell(),
            first_towns[i]->getrightcell(),
            first_towns[i]->getbottomcell(),
        };

        // On parcours toutes les cellules adjacentes
        for (Cell *cell : adjacent_cells)
        {
            if (cell != nullptr)
            { // On check si la cellule est valide
                // On récupère la ressource de la cellule
                Ressource ressource_card = cell->getCellRessource();

                // On donne une carte de cette ressource au propriétaire de la ville
                first_towns[i]->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(ressource_card));
            }
        }
        first_towns[i]->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(first_towns[i]->getCellRessource()));
    }

    // commencement du jeu
    int player_turn = 0;
    int number_turns = 1;
    while (players_list[player_turn]->getScore() < 20)
    {
        Player *currentPlayer = players_list[player_turn];

        std::string response;
        int random_number = rand() % 12;
        std::cout << "\n"
                  << "=============================\n"
                  << "Tour n°" << number_turns << " \n";
        std::cout << "Joueur " << players_list[player_turn]->getName() << " à vous de jouer ! \n\n";
        std::cout << "Lancement des dés 🎲🎲 \n"
                  << "Le nombre lancé est : " << random_number << std::endl;
        std::cout << "Voici la liste des cases concernés par le lancement du tirage : " << std::endl;

        // Générer la liste des cases concernés par le tirage (id des cellules ayant le numéro du dé contenu)
        std::vector<Cell *> Cell_list_dice = _board->getCellsbyDiceNumber(random_number);
        for (int i = 0; i < Cell_list_dice.size(); i++)
        {
            std::cout << "- Numéro de cellule : " << Cell_list_dice[i]->getCellID() << " & Ressource : " << Cell_list_dice[i]->getCellRessource() << std::endl;
        }

        // On parcours toutes les cellules adjacentes

        // Une fois qu'on a les id vérifier les villages adjacent et ceux des cellules pour vérifier si il y en a
        // Si un village est adjacent ou sur une cellule ,dont le numéro du dé a été tiré au sort, alors on donne la ressource présente sur la cellule
        //,dont le numéro du dé a été tiré au sort, au joueur propriétaire du village (pas uniquement au joueur qui a son tour en cours)

        for (int i = 0; i < Cell_list_dice.size() - 1; i++)
        {
            Cell *adjacent_cells[] = {
                Cell_list_dice[i]->gettopcell(),
                Cell_list_dice[i]->getleftcell(),
                Cell_list_dice[i]->getrightcell(),
                Cell_list_dice[i]->getbottomcell(),
                Cell_list_dice[i]};

            for (Cell *cell : adjacent_cells)
            {
                if (cell != nullptr && cell->getCity() != nullptr)
                { // On check si la cellule est valide
                    cell->getCity()->getOwner()->addCard(_decks->drawCardFromRessourceDeck(Cell_list_dice[i]->getCellRessource()));
                }
            }
        }

        // Déroulement d'un tour
        do
        {
            std::string response = "";
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
                      << "9. Mettre fin à votre tour : /end \n\n"
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
                            std::cout << "Votre deck (ressources identiques nécessaires) :" << std::endl;
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
                            } else {
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
                                std::cout << "Votre deck :" << std::endl;
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
                                std::cout << selectedTradePlayer->getName() << " - votre deck :" << std::endl;
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
                if (bonusCards.empty()) {
                    std::cout << "Vous n'avez aucune carte bonus à jouer." << std::endl;
                }else{
                    std::cout << players_list[player_turn]->getName() << " - votre deck :" << std::endl;
                    for (int i = 0; i < bonusCards.size(); i++)
                    {
                        std::cout << i << ": " << bonusCards[i].getTitre() << " (" << bonusCards[i].getRarete() << ")\n" << "Description : " << bonusCards[i].getDesc() << std::endl;
                    }

                    // Demander au joueur de choisir une carte bonus à jouer
                    int selectedBonus = -1;
                    while (selectedBonus < 0 || selectedBonus >= bonusCards.size()) {
                        std::cout << "Entrez le numéro de la carte bonus que vous souhaitez jouer : ";
                        std::cin >> selectedBonus;

                        if (selectedBonus < 0 || selectedBonus >= bonusCards.size()) {
                            std::cout << "Numéro invalide, veuillez réessayer." << std::endl;
                        }
                    }

                    // Vérifier l'état de la carte et lancer l'effet si elle peut être utilisée
                    Card& chosenCard = bonusCards[selectedBonus];
                    if (chosenCard.getStatus() == NotUse) {
                        std::cout << "Vous jouez la carte bonus : " << chosenCard.getTitre() << std::endl;
                        // Lancer l'effet de la carte
                        if (chosenCard.getType() ==ressource){
                            std::cout << "Cette commande est impossible sur une carte ressource" << std::endl;
                        } else{
                            if (chosenCard.getId() == "stoleACardToAPlayer") {
                                std::cout << "Effet activé : Voler une carte à un joueur.\n";
                                // Implémentation pour voler une carte à un joueur
                                // Exemple : demander au joueur de choisir un adversaire et une carte ressource à voler
                               std::cout << "Voici la liste des joueurs : " << std::endl;
                               for (int i = 0; i < player_count; i++)
                               {
                                std::cout << std::to_string(i+1) << ". " << players_list[i]->getName();
                               }
                               int targetPlayer;
                               do {
                                 std::cout << "Choisissez un joueur chez qui voler une carte : " << std::endl;
                                    std::cin >> targetPlayer;
                               } while(players_list[targetPlayer-1]->getName() == players_list[player_turn]->getName());
                               if (players_list[targetPlayer-1]->getDeck().size() == 0){
                                std::cout << "Vous avez mal choisi, le joueur désigné n'a plus de cartes..." << std::endl; 
                               } else{
                                    int numberChoose = -1;
                                    int numbers_cards = players_list[targetPlayer-1]->getDeck().size() -1;
                                    while (numberChoose < 0 || numberChoose > numbers_cards){
                                        std::cout << "Choisissez un nombre entre 0 et " << numbers_cards << " : ";
                                        std::cin >> numberChoose;
                                    }
                                    // Valou je te laisse finir
                                    //players_list[player_turn]->addCard(players_list[targetPlayer-1]->getDeck().erase(numberChoose))
                                    

                               }
                               

                            } 
                            else if (chosenCard.getId() == "doubleRessourcesDuringOneTurn") {
                                std::cout << "Effet activé : Doubler les ressources pendant un tour.\n";
                                // Implémentation pour doubler les ressources du joueur pendant un tour
                                //doubleResourcesForTurns(1);
                            } 
                            else if (chosenCard.getId() == "BlockCellDuringTwoTurn") {
                                std::cout << "Effet activé : Bloquer une cellule pendant deux tours.\n";
                                // Implémentation pour bloquer une cellule ressource pendant 2 tours
                                //blockCellForTurns(2);
                            } 
                            else if (chosenCard.getId() == "stoleACardToAllPlayers") {
                                std::cout << "Effet activé : Voler une carte à tous les joueurs.\n";
                                // Implémentation pour voler une carte à tous les joueurs
                                //stealCardFromAllPlayers();
                            } 
                            else if (chosenCard.getId() == "doubleRessourcesDuringThreeTurns") {
                                std::cout << "Effet activé : Doubler les ressources pendant trois tours.\n";
                                // Implémentation pour doubler les ressources du joueur pendant 3 tours
                                //doubleResourcesForTurns(3);
                            } 
                            else if (chosenCard.getId() == "BlockCellDuringFiveTurns") {
                                std::cout << "Effet activé : Bloquer une cellule pendant cinq tours.\n";
                                // Implémentation pour bloquer une cellule ressource pendant 5 tours
                                //blockCellForTurns(5);
                            } 
                            else if (chosenCard.getId() == "WinOnePoint") {
                                std::cout << "Effet activé : Gagner un point.\n";
                                // Implémentation pour ajouter 1 point au joueur
                                //addPointsToPlayer(1);
                            } 
                            else if (chosenCard.getId() == "WinThreePoints") {
                                std::cout << "Effet activé : Gagner trois points.\n";
                                // Implémentation pour ajouter 3 points au joueur
                                //addPointsToPlayer(3);
                            } 
                            else if (chosenCard.getId() == "stoleARessourceToAllPlayers") {
                                std::cout << "Effet activé : Voler une ressource à tous les joueurs.\n";
                                // Implémentation pour voler toutes les ressources d'un type à tous les joueurs
                                //stealRessourceFromAllPlayers();
                            } 
                            else if (chosenCard.getId() == "DestroyASmallTown") {
                                std::cout << "Effet activé : Détruire un village.\n";
                                // Implémentation pour détruire un village
                                //destroySmallTown();
                            } 
                            else if (chosenCard.getId() == "BlockACityDuringFourTurns") {
                                std::cout << "Effet activé : Bloquer une ville pendant quatre tours.\n";
                                // Implémentation pour bloquer une ville pendant 4 tours
                                //blockCityForTurns(4);
                            } 
                            else if (chosenCard.getId() == "DestroyRessource") {
                                std::cout << "Effet activé : Détruire une ressource.\n";
                                // Implémentation pour détruire une ressource (case ressource devient inutilisable)
                                //destroyRessource();
                            } 
                            else {
                                std::cout << "Effet inconnu. Aucune action n'a été exécutée.\n";
                            }

                        }

                        // Mettre à jour le statut de la carte
                        chosenCard.setStatus(Using);
                    } else if (chosenCard.getStatus() == Using) {
                        std::cout << "Cette carte est déjà en cours d'utilisation." << std::endl;
                    } else {
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
                Player *currentPlayer = players_list[number_turns]; 
                currentPlayer->printDeck();

                // Montrer le plateau si besoin
                std::cout << "Visualiser le plateau ? (oui/non) : ";
                std::string response = "";
                std::cin >> response;
                if (response == "oui")
                {
                    _board->printBoard();
                }

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
                    } else if (cell->getState() != normal) {
                        std::cout << "Cette case a été détruite ou est bloquée." << std::endl;
                        available = false;
                    } else if (cell->getCity() != nullptr) {
                        std::cout << "Une ville existe déjà sur cette case." << std::endl;
                        available = false;
                    } else {
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
                        std::cout << "Village construit." << std::endl;
                    } 
                }
            }
            else if (response == "/level-up")
            {
                // Montrer le coût d'une ville
                // Montrer le deck du joueur
                // Demander confirmation de la construction ainsi que la case visée (proposer les cases ayant déjà les villages de l'utilisateur)
                // Vérifier que la construction est possible (un village du joueur est déjà présent sur la case et l'utiliasteur possède les ressources nécessaires)
                // Améliorer le village en ville
            }
            else if (response == "/build-bonus")
            {
                // Montrer le coût des cartes bonus
                std::cout << "COUT DES CARTES BONUS" << std::endl;
                std::cout << "- Carte bonus commune : 2 Acier – 5 Bois – 2 Sable – 1 Pierre – 3 Nourriture \n- Carte bonus rare : 4 Acier – 5 Bois – 3 Pierre – 4 Nourriture – 4 Blé – 5 Sable\n- Carte bonus épique : 1 Or – 2 Argent – 5 Bois – 5 Acier – 5 Nourriture – 4 Blé" << std::endl;

                // Montrer le deck du joueur
                Player *currentPlayer = players_list[number_turns];
                currentPlayer->printDeck();

                // Demander la rareté de la carte voulu
                std::string rarity = "Default";
                while (rarity != "commun" || rarity != "rare" || rarity != "epique")
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
                    else
                    {
                        // Carte default non supporté ou bonus
                    }
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
                        std::cout << "Vous possèdez les ressources nécéssaires";
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires";
                    }
                }
                else
                {
                    // commun
                    if (acier >= 2 && bois >= 5 && sable >= 2 && pierre >= 1 && nourriture >= 3)
                    {
                        enoughRessources = true;
                        std::cout << "Vous possèdez les ressources nécéssaires";
                    }
                    else
                    {
                        std::cout << "Vous ne possèdez pas les ressources nécéssaires";
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
            }
            else if (response == "/end")
            {
                std::cout << "Vous avez décidé de mettre fin à votre tour : " << players_list[player_turn]->getName() << "\n\n"
                          << "=======================================\n";
                break;
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

    return 0;
};