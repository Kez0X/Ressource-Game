#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.hpp"

class Player
{
private:
    // données privées pour les garder au sein du programme
    std::string _name;
    std::vector<Card> _deck;
    int _bonus;
    int _score;

public:
    // Constructeurs
    Player(std::string);
    Player(std::string, int);
    Player(std::string, std::vector<Card>);
    Player(std::string, std::vector<Card>, int, int);

    // Getters
    std::string getName();
    std::vector<Card> getDeck();
    std::vector<Card> getDeckFilter(TypeCard);
    int getBonus();
    int getScore();

    // Setters
    void setName(std::string);
    void setBonus(int);
    void setScore(int);
    void setDeck(std::vector<Card>);

    // Méthodes
    // Utilisation de ces méthodes au sein d'autres classes
    void addCard(Card);
    void printDeck();
    void printDeckBonus();
};

#endif